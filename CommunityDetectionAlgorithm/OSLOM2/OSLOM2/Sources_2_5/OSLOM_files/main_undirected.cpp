

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                               *
 *	This program is free software; you can redistribute it and/or modify         *
 *  it under the terms of the GNU General Public License as published by         *
 *  the Free Software Foundation; either version 2 of the License, or            *
 *  (at your option) any later version.                                          *
 *                                                                               *
 *  This program is distributed in the hope that it will be useful,              *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of               *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                *
 *  GNU General Public License for more details.                                 *
 *                                                                               *
 *  You should have received a copy of the GNU General Public License            *
 *  along with this program; if not, write to the Free Software                  *
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA    *
 *                                                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                               *
 *  Created by Andrea Lancichinetti on 15/5/09 (email: arg.lanci@gmail.com)      *
 *  Location: ISI foundation, Turin, Italy                                       *
 *                                                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include "standard_package/standard_include.cpp"


#include "log_table.h"





double log_fact_table::right_cumulative_function(int k1, int k2, int tm, int x) {

	if(x>k1 || x>k2)
		return 0;
	
	
	if(k1*k1<tm)
		return cum_hyper_right(x, k2, tm, k1);
	
	
	// k1 is the degree of the node
	// k2 is the degree of the other node (the bigger)
	// k3 is 2m - k1 - k2
	
	
	int k3=tm -k1;
	
	int H=(k3 - k1 -k2) /2;
	int l1=max(0, -H);
	
	if(x==l1)
		return 1;
	
	
	int mode= max(cast_int( k2 / double(k1+k3) * k1), l1);		// this mode in underestimated anyway
	if(mode>k2)
		mode=k2;
	
	//cout<<"mode: "<<mode<<endl;
	if(x<mode)
		return cum_hyper_right(x, k2, tm, k1);
	
	
	return fast_right_cum_symmetric_eq(k1, k2, H, x, mode, tm);

}






#include "set_parameters.h"

log_fact_table LOG_TABLE;
Parameters paras;



#include "module_collection.h"
#include "undir_weighted_tabdeg.h"



#include "undirected_network.h"
#include "louvain_oslomnet.h"
#include "undirected_oslomnet_evaluate.h"
#include "oslom_net_global.h"
#include "try_homeless_undir.cpp"

#include "hierarchies.h"






void program_statement(char * b) {
	
	
	cout<<"\n\n\n***************************************************************************************************************************************************"<<endl;

	cout<<"This program implements the OSLO-method for undirected networks"<<endl;
	
		
	general_program_statement(b);
	
	
	
}










int main(int argc, char * argv[]) {


	if (argc<2) {
		program_statement(argv[0]);
		return -1;
	}


	if (paras._set_(argc, argv) == false)
		return -1;

	paras.print();

	string netfile = paras.file1;


	{	/* check if file_name exists */
		char * b = new char[netfile.size() + 1];
		cast_string_to_char(netfile, b);
		ifstream inb(b);
		if (inb.is_open() == false) {

			cout << "File " << netfile << " not found" << endl;
			return false;

		}
		delete[] b;
	}	/* check if file_name exists */


	oslom_net_global luca(netfile);





	if (luca.size() == 0 || luca.stubs() == 0) {
		cerr << "network empty" << endl;
		return -1;
	}



	LOG_TABLE._set_(cast_int(luca.stubs()));



	char directory_char[1000];
	cast_string_to_char(paras.file1, directory_char);
	char char_to_use[1000];
	sprintf(char_to_use, "mkdir %s_oslo_files", directory_char);
	int sy = system(char_to_use);
	sprintf(char_to_use, "rm -r %s_oslo_files/*", directory_char);
	sy = system(char_to_use);


	cout << "output files will be written in directory: " << directory_char << "_oslo_files" << endl;

	//luca.draw_with_weight_probability("prob");
	oslom_level(luca, directory_char);


	return 0;



}








