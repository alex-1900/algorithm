## 归并排序 (Merge Sort)

### 简介
归并排序是一种采用分治策略的排序算法。将源数组不断分解为更小的子数组，分别对子数组进行排序与合并，最终得到排序好的数组。我们通常可以用递归式来描述归并排序。

![递归式结构](https://raw.githubusercontent.com/speed-sonic/algorithm/master/Algorithms/MergeSort/images/1.png "递归式结构")

### 伪代码
```go
MergeSort(A, p, r)
    if p < r
        q = (p + r) / 2
        MergeSort(A, p, q)
        MergeSort(A, q+1, r)
        Merge(A, p, q, r)

Merge(A, p, q, r)
    leftIndex = q - p + 1
    rightIndex = r - q
    let L[1...leftIndex+1] and R[1...rightIndex+1] be new arrays
    for i = 1 to leftIndex
        L[i] = A[p+i-1]
    for j = 1 to rightIndex
        R[j] = A[q+j]
    L[leftIndex+1] = ∞
    R[rightIndex+1] = ∞

    i = 1
    j = 1
    for k = p to r
        if L[i] < R[j]
            A[k] = L[i]
            i = i + 1
        else
            A[k] = R[j]
            j = j + 1
```
