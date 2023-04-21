#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <set>
#include <utility>
#include <unordered_set>
#include <map>

using namespace std;


// LeetCode代码
int largestRectangleArea(vector<int>& heights) {
	heights.push_back(-1);
	stack<int> st;
	int ret = 0, top;
	for (int i = 0; i < heights.size(); i++)
	{
		if (st.empty() || heights[st.top()] <= heights[i])
		{
            printf("入栈：%d\n",i);
			st.push(i);
		}
		else
		{
            // 栈顶高度小于等于当前高度时停止，top为当前矩形的左侧index
			while (!st.empty() && heights[st.top()] > heights[i])
			{
				top = st.top();
				st.pop();
				//i-top指的是当前矩形的宽度，heights[top]就是当前的高度
				//再次强调栈中现在为单调递增
				int tmp = (i - top)*heights[top];
                cout<<"矩形起始："<<top<<"  当前大小："<<tmp<<endl;
				if (tmp > ret)
					ret = tmp;
			}
            /* 
                将此矩形按照高度简化，例如：3,5,6,3 --> 3,3,3,3
                此方式不影响之后的计算，因为矩形的高度由它包含的最矮柱体决定
                例如：
                    3,5,6,3,4,7,5 的最大矩形面积与 3,3,3,3,4,7,5 一致
                一次计算完当前矩形面积之后，将左侧高度调整为与右侧一致，并重新入栈
            */
			st.push(top);
			heights[top] = heights[i];
		}
        printf("\n");
	}
	return ret;
}


int main()
{
    vector<int> v{2,1,3,6,5};
    cout<<largestRectangleArea(v)<<endl;
}