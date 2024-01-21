#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Activity {
    int start;
    int end;
};

bool compare(Activity a, Activity b) {
    if(a.end == b.end) return (a.start < b.start);
    return a.end < b.end;
}

int main() {
    int k;
    cin >> k;
    vector<Activity> activities(k);
    for (int i = 0; i < k; i++) {
        cin >> activities[i].start >> activities[i].end;
    }
    sort(activities.begin(), activities.end(), compare);
    vector<int> rooms;
    for (const auto& activity : activities) {
        bool found = false;
        for(int i=0;i<rooms.size();i++) {
            if(rooms[i] < activity.start){
                rooms[i] = activity.end;
                found = true;
                break;
            }
        }
        if (!found) {
            rooms.push_back(activity.end);
        }
        for(auto i:rooms){
            cout << i << " ";
        }
        cout << endl;
        
    }
    cout << rooms.size() << endl;
    
    return 0;
}