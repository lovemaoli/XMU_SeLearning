#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Activity {
    int start;
    int end;
};

bool compare(Activity a, Activity b) {
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
    for(auto i:activities){
        cout << i.start << " " << i.end << endl;
    }
    vector<int> rooms;
    for (const auto& activity : activities) {
        bool found = false;
        int dqarr=-1;
        for(int i=0;i<rooms.size();i++) {
            if(dqarr==-1){
                if(rooms[i] < activity.start){
                    dqarr = i;
                }
            }
            else{
                if(rooms[i] < activity.start) {
                    if(rooms[dqarr] < rooms[i]) {
                        dqarr = i;
                    }
                }
            }
        }
        if (dqarr!=-1) {
            rooms[dqarr] = activity.end;
            // cout << "dqarr: " << dqarr << " " << rooms[dqarr] << endl;
        }
        else if (dqarr==-1) {
            rooms.push_back(activity.end);
            // cout << "push_back: " << activity.end << endl;
        }
        for(auto i:rooms){
            cout << i << " ";
        }
        cout << endl;
    }
    cout << rooms.size() << endl;
    
    return 0;
}