#include<unordered_map>
#include<vector>
#include<string>

class Solution {
public:
    typedef long long ll;
    ll big_val = 1e10;
    unordered_map<string,vector<pair<string,ll>>> adj;
    vector<ll> dp;
    string sourceStr,targetStr;
    set<int>validLengths;
    typedef pair<ll,string> pli;
    //start -> end for dijikstra
    unordered_map<string,unordered_map<string,ll>> dijikstra_memo;

    ll dijikstra(string &src, string &tgt){

        if(dijikstra_memo.count(src) && dijikstra_memo[src].count(tgt   )){
            return dijikstra_memo[src][tgt];
        }

        priority_queue<pli,vector<pli>,greater<pli>> pq;

        unordered_map<string,ll> dist;

        dist[src] = 0;

        pq.push({0,src});

        while(!pq.empty()){
            ll currCost = pq.top().first;
            string currNode = pq.top().second;
            pq.pop();
            
            if(currCost > dist[currNode])continue;

            if(currNode == tgt){
                break;
            }

            for(auto &edge : adj[currNode]){
                string adjNode = edge.first;
                ll edgeCost = edge.second;

                if(!dist.count(adjNode) || currCost + edgeCost < dist[adjNode]){
                    dist[adjNode] = currCost + edgeCost;
                    pq.push({dist[adjNode],adjNode});
                }

            }
        }

        ll finalCost = dist.count(tgt)?dist[tgt]:big_val;

        return dijikstra_memo[src][tgt] = finalCost;
    }

    ll solve(int idx){
        if(idx >= sourceStr.length()){
            return 0;
        }
        if(dp[idx] != -1)return dp[idx];

        

        ll minCost = big_val;

        if(sourceStr[idx] == targetStr[idx]){
            minCost = solve(idx+1);
        }

        for(auto &len : validLengths){
            // Check if substring is valid
            if(idx + len > sourceStr.length())continue;
            
            string srcSub = sourceStr.substr(idx,len);
            string tgtSub = targetStr.substr(idx,len);

            if(!adj.count(srcSub))continue;

            ll minPathCost = dijikstra(srcSub,tgtSub);

            if(minPathCost == big_val)continue;

            minCost = min(minCost, minPathCost + solve(idx + len));

        }

        return dp[idx] = minCost;
    }

    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        adj.clear();
        validLengths.clear();
        dijikstra_memo.clear();

        sourceStr = source, targetStr = target;
        
        int n = original.size();

        dp.assign(sourceStr.length()+1, -1);
        
        for(int i = 0; i < n ; i++){
            adj[original[i]].push_back({changed[i],cost[i]});
        }

        for(auto &it:original){
            validLengths.insert(it.length());
        }

        ll res = solve(0);

        return res==big_val?-1:res;

    }
};