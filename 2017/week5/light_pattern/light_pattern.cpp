#include <iostream>
#include <vector>

using namespace std;


void do_testcases(){
	int num_bulbs, len_pattern, pattern;
	cin >> num_bulbs >> len_pattern >> pattern;
	
	vector<bool> bulb_state(num_bulbs);
	
	// read in current state
	for(int i=0; i<num_bulbs; ++i){
		int state; cin >> state;
		bulb_state[i] = state == 1;
	}
	
	// read in pattern
	vector<bool> pattern_state(len_pattern);
	for(int i = len_pattern; i > 0; --i) {
		pattern_state[i] = pattern & 0x1;
		pattern = pattern >> 1;
	}
	
	int num_blocks = num_bulbs/len_pattern;
	int all_num_bulb_changes = 0; // all single bulbes changes
	int all_num_total_changes = 1; // all all changed
	
	// for all block, starting with the last one
	for(int block = num_blocks; block > 0; --block){
		int start = (block-1) * len_pattern;
			
		int num_bulb_changes = 0;
		int num_total_changes = 0;
			
		for(int position = 0; position < len_pattern; ++position){
			// if it is different we have to pay to change, if it is equal we  have to pay if we change all
			if(pattern_state[start+position] != bulb_state[start+position]){
				++num_bulb_changes;
			}else{
				++num_total_changes;
			}
		}
		
		
		int tmp_total_change = min(
                // already swapped till at least previously visited block
                min(
                    all_num_total_changes + num_total_changes, // swapped including current block
                    all_num_total_changes + 2 + num_bulb_changes // swapped over our block, swap back, single changes for block, swap back before current block
                ),
                // not swapped yet
                min(
                    all_num_bulb_changes + 1 + num_total_changes, // we swap till current block and do swapping changes
                    all_num_bulb_changes + 1 + num_bulb_changes // we swap till the next block and do normal changes in current block 
                    )
                );

       int tmp_single_change = min(
                // not swapped yet
                min(
                    all_num_bulb_changes + num_bulb_changes, // we just change each bulb by itself
                    all_num_bulb_changes + 2 + num_total_changes // swap, change swapped, swap back
                    ),
                // swapped already
                min(
                    all_num_total_changes + 1 + num_bulb_changes, // swap back, do normal changes 
                    all_num_total_changes + 1 + num_total_changes
                    )
				);
		
	all_num_total_changes = tmp_total_change;
	all_num_bulb_changes = tmp_single_change;
	}
	cout << min(all_num_total_changes, all_num_bulb_changes) << endl;
}


int main(){
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
