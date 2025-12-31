/*
This is a simple explanation of the reason why Dijkstra's algorithm works well with directed/undirected graphs
with non-negative edges.

Initially we are not_sure of the shortest_distance for any node. So, all of the vertices are in one team named "not_sure."
Later, we will divide them into two groups, and besides this "not_sure" group, a new group named "sure" will be formed.
At first, we store the initial values of shortest distance from root, for every node. In this case, root->root distance
is zero, and root->all other nodes is inifinity as we could not reach any other node yet. This is actually our base case.

Now we choose the node with smallest distance from the not_sure team. We choose this node deliberately as a part of our 
greedy choice, since choosing any other node will eventually result in larger distances, and that's why Dijkstra is called 
a greedy algorithm. Then from this currently chosen node, we try to update all its neighbours if possible. After this,
we do a weird thing and that is "We put this current node into the sure team!!!". But why take this decision?? Answer is:
say, our current node is named "A". Now the nodes which are in the sure team, have already tried their best to decrease
the distance root->A. So, any member of "Sure" team cannot make any further improvement to the shortest distance of A.
Again, for all nodes in not_sure team, they themselves have larger distances than A (as A was chosen greedily), so how 
can they improve the distance of A (as we are considering that our graph has no negative weight edge)??? That's why, we
take the decision that no other node can further update the shortest distance of A from root in a meaningful way, and finally
we grant A to be a sure node!! 
In this way, we gradually take each node in sure team, and after 'n' iterations, we are done with our job!!

Thank you for reading.
*/