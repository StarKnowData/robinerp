using System;
using System.Collections.Generic;
using System.Text;

namespace QPS.NEW.Model
{
    [Serializable]
    public class Poster
    {
        public Poster()
        {
            Id = -999;
        }

        public int Id;
        public string PhotoUrl;
        public string URL;
    }
}
