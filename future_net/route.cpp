
#include "route.h"
#include "search.h"
#include "lib_record.h"
#include <stdio.h>

using namespace code;

class VerTex
{
    public:
	VerTex()
		{
		    LinkID = -1;       //初始有向边的索引为-1
		    Cost = -1;        //初始化权值默认为-1
		}
	int LinkID;
	int Cost;
};

//全局变量 
VerTex graph_matrix[MAX_VERTEX_NUMS][MAX_VERTEX_NUMS];  //50*50的临接矩阵

//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{ 
    unsigned short result[] = {1, 6, 4};
    CodeCraft craft(edge_num);
    craft.demand_to_num(demand);
    craft.build_graph(topo, edge_num);
    craft.dfs_solution();
    for (int i = 0; i < craft.gPathSize; i++)
        record_result(craft.gMinPath[i]);
}

void CodeCraft::dfs_solution()
{
    int visited[MAX_VERTEX_NUMS] = {0};
    int cur_cost = 0;
    dfs_best_paths(cur_cost, this->gStartVex, visited);
}

void CodeCraft::dfs_best_paths(int pre_cost, int start, int * visited)
{
    int i = 0;  
    static int path_size = 0;  
    static int cur_cost = 0;//当前路径代价  
    static int path_count = 0;//当前符合要求的路径条数  
    static int path_stack[2000] = { 0 };  
  
    visited[start] = 1;  
    if (start == this->gEndVex){//如果是终点  
        i = 0;  
        bool flag = true;  
        while (i < gMustNums)//检查是否全部必经点都访问过  
        {  
            if (visited[this->gMustPass[i]] != 1)  
            {  
                flag = false;//没有经过所有必经点  
                break;  
            }  
            i++;  
        }  
        if (flag && this->gMinCost> cur_cost)//必经点全部都访问过,并且当前路径权值更小，就记录路径  
        {  
            this->get_new_path(path_stack, path_size, cur_cost);//更新最短路径  
            path_count++;  
        }  
    }  
    else{  
        int nextVex = 0,curVex = start;  
        bool flagfirst = true;  
        while (nextVex != -1)//如果存在相邻点  
        {  
            nextVex = next_adj_vertex(curVex, nextVex, flagfirst);//curVex相邻的下一个顶点
            if (nextVex != -1 && visited[nextVex] == 0)//如果该相邻的顶点没有被访问过  
            {  
                //cout<<"-------x-------:"<<curVex<<"-------y------:"<<nextVex<<endl;
                path_stack[path_size++] = graph_matrix[curVex][nextVex].LinkID;  
                cur_cost += graph_matrix[curVex][nextVex].Cost;  
                dfs_best_paths(graph_matrix[curVex][nextVex].Cost, nextVex, visited);  
            }  
            flagfirst = false;  
        }  
    }  
    path_size--;  
    cur_cost -= pre_cost;  
    visited[start] = 0;  

}

void CodeCraft::get_new_path(int * pResultPath, int path_size, int curCost)
{
    this->gMinCost= curCost;  
    this->gPathSize= path_size;  
    for (int i = 0; i < path_size; i++)  
        this->gMinPath[i]= pResultPath[i];  
}

int CodeCraft::next_adj_vertex(int curVex, int nextVex, bool flagfirst)
{
    int i = nextVex;  
    if (!flagfirst)  
        i++;  
    for (; i < gVertTexNums; i++)  
    {  
        if (graph_matrix[curVex][i].Cost != -1)  
            return i;  
    }  
    return -1;  
}

void CodeCraft::build_graph(char * * const topo, int const edge_nums)
{
     if(topo == NULL)
	 	return;
     map<pair<int,int>,int>mapping;
     int vertTexNums = 0;
     int num[4] = {0};
     for(int i = 0; i < edge_nums; i++)
     	{
     	     edge_to_num(topo[i], num);
	     //没有对应的权值
	     if(mapping.find(pair<int,int>(num[1],num[2])) == mapping.end()){
		 graph_matrix[num[1]][num[2]].LinkID = num[0];
		 graph_matrix[num[1]][num[2]].Cost   = num[3];
		 mapping[pair<int,int>(num[1],num[2])] = num[3];
	     }
	     if(num[1] > vertTexNums)
		vertTexNums = num[1]+1;
	     if(num[2]>vertTexNums)
		vertTexNums = num[2]+1;
     	}
    for(int i = 0; i < vertTexNums; i++){
	graph_matrix[i][i].Cost = -1;
    }
    this->gVertTexNums = vertTexNums;
}

void CodeCraft::edge_to_num(char * one_edge, int * num)
{
     int i = 0;  
     char *temp_str[10];  
  
    while ((temp_str[i] = strtok(one_edge, ",")) != NULL)  
    {  
        num[i] = atoi(temp_str[i]);  
        i++;  
        one_edge = NULL;  
    } 
}

void CodeCraft::demand_to_num(char * const demand)
{
     int i = 0;
     int length = strlen(demand);
     if(demand[length-1] == '\n')
	 	length--;
     while(i < length && demand[i] != ',')
	 this->gStartVex = 10* this->gStartVex+demand[i++] - '0';
     i++;
     while(i < length && demand[i] != ',')
	 this->gEndVex = 10*this->gEndVex+demand[i++] - '0';
    int size = 0;
    for(i++; i < length; i++){
	while(i < length && demand[i] != '|')
		this->gMustPass[size] = 10*this->gMustPass[size]+demand[i++] - '0';
	size++;
    }
   this->gMustNums = size;
   
}