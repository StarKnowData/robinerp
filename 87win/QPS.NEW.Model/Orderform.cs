using System;


namespace QPS.NEW.Model
{
    [Serializable]
    public class Orderform
    {
        private decimal? Beveragecost_;

        public decimal? Beveragecost
        {
            get { return Beveragecost_; }
            set { Beveragecost_ = value; }
        }


        private DateTime? endTime_;

        public DateTime? endTime
        {
            get { return endTime_; }
            set { endTime_ = value; }
        }


        private int Id_;

        public int Id
        {
            get { return Id_; }
            set { Id_ = value; }
        }



        private int IsDelete_;

        public int IsDelete
        {
            get { return IsDelete_; }
            set { IsDelete_ = value; }
        }


        private int? IsValidity_;

        public int? IsValidity
        {
            get { return IsValidity_; }
            set { IsValidity_ = value; }
        }


        private string OrderNumber_;

        public string OrderNumber
        {
            get { return OrderNumber_; }
            set { OrderNumber_ = value; }
        }


        private int Roomid_;

        public int Roomid
        {
            get { return Roomid_; }
            set { Roomid_ = value; }
        }


        private int? RoomType_;

        public int? RoomType
        {
            get { return RoomType_; }
            set { RoomType_ = value; }
        }


        private DateTime? StartTime_;

        public DateTime? StartTime
        {
            get { return StartTime_; }
            set { StartTime_ = value; }
        }


        private int Userid_;

        public int Userid
        {
            get { return Userid_; }
            set { Userid_ = value; }
        }


    }
}
