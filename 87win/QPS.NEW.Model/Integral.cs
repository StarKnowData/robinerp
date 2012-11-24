using System;


namespace QPS.NEW.Model
{
    [Serializable]
    public class Integral
    {
        public Integral()
        {
            Content_ =null;
            Id_ = -999;
            OrderId_ = null;
            RoomId_ = null;
            CreateTime_ = null;
        }

        private int? Content_;

        public int? Content
        {
            get { return Content_; }
            set { Content_ = value; }
        }


        private DateTime? CreateTime_;

        public DateTime? CreateTime
        {
            get { return CreateTime_; }
            set { CreateTime_ = value; }
        }


        private int Id_;

        public int Id
        {
            get { return Id_; }
            set { Id_ = value; }
        }


        private int? OrderId_;

        public int? OrderId
        {
            get { return OrderId_; }
            set { OrderId_ = value; }
        }


        private int? RoomId_;

        public int? RoomId
        {
            get { return RoomId_; }
            set { RoomId_ = value; }
        }


        private string UserID_;

        public string UserID
        {
            get { return UserID_; }
            set { UserID_ = value; }
        }
    }
}
