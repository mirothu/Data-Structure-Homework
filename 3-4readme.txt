A.本题中我们需要频繁的查找已有的姓名并在未找到时建立新的数据，因此我使用了二叉搜索树来实现所需的功能，并实现了查找等方法。
主要实现的算法是查找，在该算法中，我使用了标准的字符串比较函数strcmp，该函数在字典序下分别返回负值、0和正值，分别对应a<b,a=b,a>b。在这个基础上我们可以以strcmp的结果来进行查找，负值则向左子树方向递归查找，正值则向右子树方向递归查找，返回0则代表该节点即是我们查找的节点，此时将其计数器++即可。

B.在本题中我使用的二叉搜索树由于时间限制是未进行平衡处理的，若进行平衡处理可以使运行时间更短。

C.空间复杂度：本题中我们只用到了二叉搜索树，其节点个数等于同学的总数，即空间上是O（m）的（记m为同学总数）。
时间复杂度：本题中由于未做平衡处理，因此我们每次查找花费的时间是O（n）的，而我们一共需要n次查找等操作，因此总的时间复杂度是O（mn）的。