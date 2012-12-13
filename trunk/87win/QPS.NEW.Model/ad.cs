using System;
using System.Collections.Generic;
using System.Text;

namespace QPS.NEW.Model
{
    public class ad
    {
        public ad()
        {
            Id_ = -999;
        }

        private string AdDate_;

        public string AdDate
        {
            get { return AdDate_; }
            set { AdDate_ = value; }
        }
        private string AdImg_;

        public string AdImg
        {
            get { return AdImg_; }
            set { AdImg_ = value; }
        }
        private string AdName_;

        public string AdName
        {
            get { return AdName_; }
            set { AdName_ = value; }
        }
        private string AdType_;

        public string AdType
        {
            get { return AdType_; }
            set { AdType_ = value; }
        }
        private string AdUrl_;

        public string AdUrl
        {
            get { return AdUrl_; }
            set { AdUrl_ = value; }
        }
        private string Catid_;

        public string Catid
        {
            get { return Catid_; }
            set { Catid_ = value; }
        }
        private int Id_;

        public int Id
        {
            get { return Id_; }
            set { Id_ = value; }
        }
    }
}
