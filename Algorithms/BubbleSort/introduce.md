## 冒泡排序 (Bubble Sort)

### 简介
冒泡排序是最简单（但不是最有效）的排序算法之一！想象一串大小不一的气泡，较小的气泡从最底层向上冒出，最终形成有规律的排列。

![瓶中气泡](https://raw.githubusercontent.com/speed-sonic/algorithm/master/Algorithms/BubbleSort/images/1.png "瓶中气泡")

冒泡排序原理很简单，但性能并不好，时间复杂度为 `O(n²)`，但比较稳定，也容易实现，所以在一些输入规模较小，或对性能要求不高的场景下很常见，总体来说是一种非常流行的排序算法！

### 伪代码
```go
// 升序排列
BUBBLE_SORT(A)
    for i = 1 to A.length - 1
        for j = 1 to A.length - i
            if A[j] > A[j+1]
                交换 A[j] 和 A[j+1]
    return A
```