/* Copyright (c) 2018 Baidu, Inc. All Rights Reserved.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0
   
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. 
*/

#ifndef ANAKIN_FRAMEWORK_LITE_CODE_GEN_BASE_H
#define ANAKIN_FRAMEWORK_LITE_CODE_GEN_BASE_H

#include "framework/graph/graph.h"

namespace anakin {

namespace lite {

/**  
 *  \brief class for target language code generator.
 *
 */
template<typename Ttype, DataType Dtype, Precision Ptype>
class CodeGenBase {
public:
	CodeGenBase() {}
	virtual ~CodeGenBase(){}

	virtual void gen_files() {}

	/**
	 *  \biref initial graph msg
	 */
	bool init_graph(Graph<Ttype, Dtype, Ptype>& graph);

private:
	/**
	 * \brief analyse the memory reuse info
	 */
	bool init_memory_info();

	/**
	 * \brief serialization of weights
	 */
	bool serialize_weights();

private:
	Graph<Ttype, Dtype, Ptype> _graph;
	std::vector<std::string> _exec_op_order; /// running order of operation's name
	BinaryWritter _weights_io; // weight file writter
};

} /* namespace lite */

} /* namespace anakin */

#endif

