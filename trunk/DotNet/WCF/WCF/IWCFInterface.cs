﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;

namespace WCF_Server
{
    [ServiceContract]
    public interface IWCFInterface
    {
        [OperationContract]
        bool ShowOut(string str);
    }
}
