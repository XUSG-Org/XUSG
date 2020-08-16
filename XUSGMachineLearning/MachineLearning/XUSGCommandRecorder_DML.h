//--------------------------------------------------------------------------------------
// Copyright (c) XU, Tianchen. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "XUSGMachineLearning.h"

namespace XUSG
{
	namespace ML
	{
		class CommandRecorder_DML :
			public virtual CommandRecorder
		{
		public:
			CommandRecorder_DML();
			virtual ~CommandRecorder_DML();

			void Dispatch(XUSG::CommandList* pCommandList, const Dispatchable& dispatchable, const BindingTable& bindings) const;

			com_ptr<IDMLCommandRecorder>& GetDMLCommandRecorder();

		protected:
			com_ptr<IDMLCommandRecorder> m_commandRecorder;
		};
	}
}
