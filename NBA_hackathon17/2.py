import csv
from copy import deepcopy
from functools import cmp_to_key

divisions = open('divisions.csv')
divisions = list(csv.reader(divisions))[1:]
metadata = {name: {'division': division, 'conference': conference}
            for name, division, conference in divisions}

schedule = open('schedules.csv')
schedule = list(csv.reader(schedule))[1:]

all_teams = list(metadata.keys())

def wp(result):
    return 0 if result[1] == 0 else result[0] / result[1]


def win_loss(standings, team):
    record = [0, 0]
    for k, v in standings[team].items():
        record[0] += standings[team][k][0]
        record[1] += standings[team][k][1]
    return record


def division_win_loss(standings, team):
    record = [0, 0]
    for k, v in standings[team].items():
        if metadata[team]['division'] == metadata[k]['division']:
            record[0] += standings[team][k][0]
            record[1] += standings[team][k][1]
    return record


def conference_win_loss(standings, team):
    record = [0, 0]
    for k, v in standings[team].items():
        if metadata[team]['conference'] == metadata[k]['conference']:
            record[0] += standings[team][k][0]
            record[1] += standings[team][k][1]
    return record


def is_division_leader(standings, team):
    # Todo: This is naive
    division_records = []
    for k in metadata.keys():
        if metadata[team]['division'] == metadata[k]['division']:
            division_records.append((k, conference_win_loss(standings, k)))
    division_records = sorted(division_records, key=lambda x: 0 if sum(
        x[1]) == 0 else x[1][0] / sum(x[1]), reverse=True)
    if wp(division_records[0][1]) > wp(division_records[1][1]):
        return division_records[0] == team
    else:
        return False


def store_game_result(standings, winner, loser):
    standings[winner][loser][0] += 1
    standings[loser][winner][1] += 1
    return standings


def loss_rankings(standings, conference):
    results = [(win_loss(standings, team), team) for team in standings.keys(
    ) if metadata[team]['conference'] == conference]
    results = sorted(results, key=lambda x: x[0][1])

    return [i[1] for i in results]


def win_rankings(standings, conference):
    results = [(win_loss(standings, team), team) for team in standings.keys(
    ) if metadata[team]['conference'] == conference]
    results = sorted(results, key=lambda x: x[0][0], reverse=True)

    return [i[1] for i in results]


def can_win(cur_team, game_idx, standings):
    if game_idx < 800:
        return True
    remaining_schedule = schedule[game_idx + 1:]
    sim_standings = deepcopy(standings)

    # We don't care about the other conference at all. I still have some logic
    # for choosing the "correct" winner because it makes it a bit easier to
    # debug
    def wrong_conference(_date, team_h, team_a, _score_h, _score_a, winner):
        nonlocal sim_standings
        if (metadata[team_a]['conference'] != metadata[cur_team]['conference'] and
                metadata[team_h]['conference'] != metadata[cur_team]['conference']):
            if winner == 'Home':
                sim_standings = store_game_result(
                    sim_standings, team_h, team_a)
            elif winner == 'Away':
                sim_standings = store_game_result(
                    sim_standings, team_a, team_h)
            return True
        return False

    # if it involves our team, we always want that
    # team to win
    def involves_cur_team(_date, team_h, team_a, _score_h, _score_a, _winner):
        nonlocal sim_standings
        if team_h == cur_team:
            sim_standings = store_game_result(sim_standings, team_h, team_a)
            return True
        elif team_a == cur_team:
            sim_standings = store_game_result(sim_standings, team_a, team_h)
            return True
        return False

    # If it's between a team in our conference and a team in another
    # conference, we always want the team in the other conference to win
    def interconference_play(_date, team_h, team_a, _score_h, _score_a, _winner):
        nonlocal sim_standings
        if metadata[team_a]['conference'] != metadata[team_h]['conference']:
            if metadata[team_a]['conference'] == metadata[cur_team]['conference']:
                sim_standings = store_game_result(
                    sim_standings, team_h, team_a)
            else:
                sim_standings = store_game_result(
                    sim_standings, team_a, team_h)
            return True
        return False

    # If it's between 2 teams in our conferenc, we want the team with more
    # losses than us to get it. As we assume that our team wins every single
    # game, we are still guaranteed to finish above the team with more losses.
    def above_vs_below(_date, team_h, team_a, _score_h, _score_a, _winner):
        nonlocal sim_standings
        results = loss_rankings(sim_standings, metadata[team_h]['conference'])
        if results.index(team_h) > results.index(cur_team) and results.index(team_a) < results.index(cur_team):
            sim_standings = store_game_result(sim_standings, team_h, team_a)
            return True
        elif results.index(team_a) > results.index(cur_team) and results.index(team_h) < results.index(cur_team):
            sim_standings = store_game_result(sim_standings, team_a, team_h)
            return True
        return False

    def above_vs_above(_date, team_h, team_a, _score_h, _score_a, _winner):
        nonlocal sim_standings
        results = win_rankings(sim_standings, metadata[team_h]['conference'])
        if results.index(team_h) > results.index(team_a):
            sim_standings = store_game_result(sim_standings, team_a, team_h)
            return True
        elif results.index(team_h) < results.index(team_a):
            sim_standings = store_game_result(sim_standings, team_h, team_a)
            return True
        return False

    def fallback(_date, team_h, team_a, _score_h, _score_a, winner):
        nonlocal sim_standings
        if winner == 'Home':
            sim_standings = store_game_result(sim_standings, team_h, team_a)
        elif winner == 'Away':
            sim_standings = store_game_result(sim_standings, team_a, team_h)
        return True


    rules = [wrong_conference, involves_cur_team, interconference_play,
             above_vs_below, above_vs_above] + [fallback]
    for [date, team_h, team_a, score_h, score_a, winner] in remaining_schedule:
        for f in rules:
            if f(date, team_h, team_a, score_h, score_a, winner):
                break

    results = loss_rankings(sim_standings, metadata[cur_team]['conference'])
    cur_team_idx = results.index(cur_team)
    win_tiebreaker_idx = cur_team_idx
    lose_tiebreaker_idx = cur_team_idx
    while (win_tiebreaker_idx > 0 and win_loss(sim_standings, results[win_tiebreaker_idx])[1] == win_loss(sim_standings, results[cur_team_idx])[1]):
        win_tiebreaker_idx -= 1
    win_tiebreaker_idx += 1

    while (lose_tiebreaker_idx < len(results) and win_loss(sim_standings, results[lose_tiebreaker_idx])[1] == win_loss(sim_standings, results[cur_team_idx])[1]):
        lose_tiebreaker_idx += 1
    lose_tiebreaker_idx -= 1

    if win_tiebreaker_idx < 8 and lose_tiebreaker_idx >= 8:
        if abs(win_tiebreaker_idx - lose_tiebreaker_idx) == 1:
            win_team = results[win_tiebreaker_idx]
            lose_team = results[lose_tiebreaker_idx]
            h2h = standings[win_team][lose_team]
            win_division_wl = division_win_loss(sim_standings, win_team)
            lose_division_wl = division_win_loss(sim_standings, lose_team)
            win_conference_wl= conference_win_loss(sim_standings, win_team)
            lose_conference_wl= conference_win_loss(sim_standings, lose_team)
            should_swap = False
            if h2h[0] > h2h[1]:
                should_swap = False
            elif h2h[0] < h2h[1]:
                should_swap = True
            elif is_division_leader(sim_standings, win_team) and not is_division_leader(sim_standings, lose_team):
                should_swap = False
            elif not is_division_leader(sim_standings, win_team) and is_division_leader(sim_standings, lose_team):
                should_swap = True
            elif (metadata[win_team]['division'] == metadata[lose_team]['division']
             and win_division_wl[0] != lose_division_wl[0]):
                should_swap = win_division_wl[0] < lose_division_wl[0]
            else:
                # Didn't bother implementing
                should_swap = False
            if should_swap:
                results[win_tiebreaker_idx], results[lose_tiebreaker_idx] = results[lose_tiebreaker_idx], results[win_tiebreaker_idx]
        else:
            tied_teams = results[win_tiebreaker_idx: lose_tiebreaker_idx + 1]
            scores = {k: 0 for k in tied_teams}
            division_leaders = [
                i for i in tied_teams if is_division_leader(sim_standings, i)]

            tied_wl = sorted([(sum([standings[i][j][0] for j in results]), i) for i in tied_teams], reverse=True)
            division_wl = [division_win_loss(sim_standings, i) for i in tied_teams]
            conference_wl = [conference_win_loss(sim_standings, i) for i in tied_teams]
            for i in division_leaders:
                scores[i] += 10**7
            for i in tied_wl:
                scores[i[1]] += i[0]*10**5
            tied_teams = sorted(tied_teams, key = lambda x: scores[x], reverse=True)
            results[win_tiebreaker_idx : lose_tiebreaker_idx + 1] = tied_teams

    return results.index(cur_team) < 8

eliminated_teams = set()
def bin_search(l, r, cur_team):
    if l + 1 == r:
        return l
    mid = (l+r)//2
    standings = {k: {i: [0, 0] for i in metadata.keys()} for k in metadata.keys()}
    for idx, [date, team_h, team_a, score_h, score_a, winner] in enumerate(schedule):
        if winner == 'Home':
            standings = store_game_result(standings, team_h, team_a)
        elif winner == 'Away':
            standings = store_game_result(standings, team_a, team_h)
    if can_win(cur_team, mid, standings):
        return bin_search(mid, r, cur_team)
    else:
        return bin_search(l, mid, cur_team)

import csv
with open('results.csv', 'w') as csvfile:
    csv_writer = csv.writer(csvfile)
    for i in all_teams:
        game_idx = bin_search(0, len(schedule) + 1, i)
        if game_idx >= len(schedule):
            csv_writer.writerow([i, "Playoffs"])
        else:
            csv_writer.writerow([i, schedule[game_idx][0]])
