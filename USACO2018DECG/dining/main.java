/*
ID: eric_ya1
LANG: JAVA
TASK: dining
*/

// package usaco.contest2019.contest1.gold;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

/*
4 3 1
1 4 1
3 4 1
2 4 100
2 1
 */
class main {

    private static final boolean FILE = false;
    private static final String LN = System.getProperty("line.separator");

    private class Pair {
        int x, y;

        Pair(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    private class State implements Comparable<State> {
        int x, y;
        boolean ate;

        State(int x, int y, boolean ate) {
            this.x = x;
            this.y = y;
            this.ate = ate;
        }

        public int compareTo(State p) {
            return y - p.y;
        }
    }

    /**
     * O(E log V) Shortest distance from node. Updates dist[] accordingly.
     */
    private void modDijkstra(int V, ArrayList<Pair>[] adj, int[] dist1, int[] dist2, int src, int[] yum,
            boolean[] didEat) {
        boolean[] visited1 = new boolean[V];
        boolean[] visited2 = new boolean[V];
        for (int i = 0; i < V; i++) {
            dist1[i] = Integer.MAX_VALUE;
            dist2[i] = Integer.MAX_VALUE;
        }
        dist1[src] = 0;
        PriorityQueue<State> pq = new PriorityQueue<>(V);
        pq.offer(new State(src, 0, false));
        while (!pq.isEmpty()) {
            State p = pq.poll();
            if (!p.ate && !visited1[p.x]) {
                visited1[p.x] = true;
                for (Pair next : adj[p.x]) {
                    int alt = dist1[p.x] + next.y;
                    if (alt < dist1[next.x]) {
                        dist1[next.x] = alt;
                        pq.offer(new State(next.x, alt, false));
                    }

                    if (yum[next.x] > 0) {
                        alt = dist1[p.x] + next.y - yum[next.x];
                        if (alt < dist2[next.x]) {
                            dist2[next.x] = alt;
                            pq.offer(new State(next.x, alt, true));
                        }
                    }
                }
            }
            if (p.ate && !visited2[p.x]) {
                visited2[p.x] = true;
                for (Pair next : adj[p.x]) {
                    int alt = dist2[p.x] + next.y;
                    if (alt < dist2[next.x]) {
                        dist2[next.x] = alt;
                        pq.offer(new State(next.x, alt, true));
                    }
                }
            }
        }
        // System.out.println(Arrays.toString(dist1));
        // System.out.println(Arrays.toString(dist2));
        for (int i = 0; i < V - 1; i++) {
            if (dist1[i] >= dist2[i])
                didEat[i] = true;
        }
        // System.out.println();
    }

    private void run(BufferedReader f, BufferedWriter w) throws IOException {
        StringTokenizer st = new StringTokenizer(f.readLine());
        int N, M, K;
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        ArrayList<Pair>[] adj = new ArrayList[N];
        for (int i = 0; i < N; i++) {
            adj[i] = new ArrayList<>();
        }
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(f.readLine());
            int a, b, t;
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            t = Integer.parseInt(st.nextToken());
            adj[a].add(new Pair(b, t));
            adj[b].add(new Pair(a, t));
        }
        int[] yum = new int[N];
        for (int i = 0; i < K; i++) {
            st = new StringTokenizer(f.readLine());
            int pos = Integer.parseInt(st.nextToken()) - 1;
            int y = Integer.parseInt(st.nextToken());
            yum[pos] = Math.max(yum[pos], y);
        }
        boolean[] didEat = new boolean[N];
        modDijkstra(N, adj, new int[N], new int[N], N - 1, yum, didEat);
        for (int i = 0; i < N - 1; i++) {
            w.write((didEat[i] ? "1" : "0") + LN);
        }
    }

    private void runStart() throws IOException {
        BufferedReader f;
        BufferedWriter w;

        f = new BufferedReader(new FileReader("dining.in"));
        w = new BufferedWriter(new OutputStreamWriter(System.out));

        run(f, w);
        f.close();
        w.close();
    }

    public static void main(String[] args) throws IOException {
        new main().runStart();
    }

}