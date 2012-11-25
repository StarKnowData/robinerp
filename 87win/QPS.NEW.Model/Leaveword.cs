using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace QPS.NEW.Model
{
    [Serializable]
    public class Leaveword
    {
        public Leaveword()
        {
            Id = -999;
            UserID = -999;
        }

        public string Content;
        public int Id;
        public string title;
        public int UserID;
    }
}
