import torch
import torch.nn.functional as F


def fitConstraints(X):
    if metric == 'linf':
        return X.sign()*epsilon
    elif metric == 'l2':
        flattened = X.view(X.size()[0], -1)
        print(flattened[0])
        print(flattened[0].norm())
        print(flattened[0].size())
        result = (F.normalize(flattened, p=2, dim=0)*epsilon).reshape(X.size())
        print(F.normalize(flattened, p=2, dim=0)[0])
        print(F.normalize(flattened, p=2, dim=0)[0].norm())
        print(epsilon)
        print('---')
        return result
