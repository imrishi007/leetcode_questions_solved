class Solution {
public:
    typedef pair<int,int> p;
    int minCost(int n, vector<vector<int>>& edges) {
        unordered_map<int,vector<p>> adj;

        for(auto &e : edges){
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], 2 * e[2]});
        }

        priority_queue<p,vector<p>,greater<p>> pq;
        vector<int> dist (n, INT_MAX);
        dist[0] = 0;
        pq.push({0,0});

        while(!pq.empty()){
            int d = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            if(node == n-1){
                return dist[n-1];
            }

            for(auto &p : adj[node]){
                int adjNode = p.first;
                int edW = p.second;

                if(d + edW < dist[adjNode]){
                    dist[adjNode] = d + edW;
                    pq.push({dist[adjNode], adjNode});
                }
            }
        }
        return -1;
    }
};