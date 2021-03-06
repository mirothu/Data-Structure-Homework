A.本题中主要使用了manacher算法，而由于该算法对数据结构要求较低，我只采用了字符数组来存储数据。

manacher算法的主要思路为：先对源字符串进行预处理，在每个字符之间加入字符串中未出现的字符，如#，并在首尾加上不同的字符以区分首尾。之后从第一个字符开始，以其为中心向两边展开，找到最长的回文串并存储长度。并且实时更新当前中心字符C和最右字符R的位置，而对于位置i的字符，其必然在C的右侧，取其左侧对称元素的数据t，若i+t大于R，则应取R-i，并在结束这一操作后以i为中心继续向两侧延伸并更新C和R。不断操作之后可获得所有字符作为中心时的最长回文串，将其取半并向上取整再求和即可得回文串个数。

B.本题在实现时遇到了超时的问题，通过检测发现问题出现在了预处理添加#上。在考虑了问题之后，我认为主要的问题应该是在逐个添加#并读入单个字符花费的时间过多，因此我决定使用memset先将整个字符串全部覆盖为#，再逐一更改为相应的字符。

C.空间复杂度：主要用来存储字符串和最长回文串长度，这与字符串长度n成正比，即O（n）。

时间复杂度：读入和预处理操作的时间是O（n）的，而Manacher算法是线性复杂度的算法，因此总的时间复杂度为O（n）。