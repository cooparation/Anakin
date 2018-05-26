/* Copyright (c) 2016 Anakin Authors All Rights Reserve.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */

#ifndef ANAKIN_SABER_FUNCS_IMPL_X86_SABER_POOLING_H
#define ANAKIN_SABER_FUNCS_IMPL_X86_SABER_POOLING_H

#include "saber/funcs/impl/impl_define.h"
#include "saber/saber_types.h"
#include "saber/funcs/impl/impl_base.h"
#include "saber/saber_funcs_param.h"
#include "saber/funcs/impl/x86/kernel/jit_uni_pool_kernel_f32.h"
#include "saber/funcs/impl/x86/kernel/jit_generator.h"

namespace anakin{
namespace saber {

using namespace jit;

template <DataType OpDtype ,
        DataType inDtype,
        DataType outDtype,
        typename LayOutType_op,
        typename LayOutType_in,
        typename LayOutType_out>
class SaberPooling<X86, OpDtype, inDtype, outDtype,
        LayOutType_op, LayOutType_in, LayOutType_out> : public ImplBase<
        Tensor<X86, inDtype, LayOutType_in>,
        Tensor<X86, outDtype, LayOutType_out>,
        Tensor<X86, OpDtype, LayOutType_op>,
        PoolingParam<Tensor<X86, OpDtype, LayOutType_op> > >
{
public:
    typedef Tensor<X86, inDtype, LayOutType_in> DataTensor_in;
    typedef Tensor<X86, outDtype, LayOutType_out> DataTensor_out;
    typedef Tensor<X86, OpDtype, LayOutType_op> OpTensor;

    SaberPooling()
            : kernel_(nullptr)
    {}

    ~SaberPooling() {
        if (kernel_ != nullptr) {
            delete kernel_;
        }
    }

    virtual SaberStatus init(const std::vector<DataTensor_in*>& inputs,
                             std::vector<DataTensor_out*>& outputs,
                             PoolingParam<OpTensor> &param,
                             Context<X86> &ctx) override;

    virtual SaberStatus create(const std::vector<DataTensor_in*>& inputs,
                               std::vector<DataTensor_out*>& outputs,
                               PoolingParam<OpTensor> &param,
                               Context<X86> &ctx) override;

    virtual SaberStatus dispatch(const std::vector<DataTensor_in*>& inputs,
                                 std::vector<DataTensor_out*>& outputs,
                                 PoolingParam<OpTensor> &param) override;

    virtual SaberStatus init_conf(jit_pool_conf_t &jpp,
                                  const std::vector<DataTensor_in*>& inputs,
                                  std::vector<DataTensor_out*>& outputs,
                                  PoolingParam<OpTensor>& param);
private:
    jit_uni_pool_kernel_f32<avx512_common> *kernel_;
};


}
}

#endif