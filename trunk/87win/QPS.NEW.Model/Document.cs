using System;


namespace QPS.NEW.Model
{
    public class Document
    {
        public Document()
        {
            Id_ = -999;
        }

        private string DContent_;

        public string DContent
        {
            get { return DContent_; }
            set { DContent_ = value; }
        }


        private string DTime_;

        public string DTime
        {
            get { return DTime_; }
            set { DTime_ = value; }
        }


        private string DTity_;

        public string DTity
        {
            get { return DTity_; }
            set { DTity_ = value; }
        }


        private string DType_;

        public string DType
        {
            get { return DType_; }
            set { DType_ = value; }
        }


        private int Id_;

        public int Id
        {
            get { return Id_; }
            set { Id_ = value; }
        }
    }
}
