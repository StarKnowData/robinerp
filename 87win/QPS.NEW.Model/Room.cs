using System;
using System.Collections.Generic;
using System.Text;

namespace QPS.NEW.Model
{
    [Serializable]
    public class Room
    {
        private string roomAddress_;
        public string Address
        {
            get { return roomAddress_; }
            set { roomAddress_ = value; }
        }


        private string roomAre_;
        public string Are
        {
            get { return roomAre_; }
            set { roomAre_ = value; }
        }


        private string roomContent_;
        public string Content
        {
            get { return roomContent_; }
            set { roomContent_ = value; }
        }


        private int roomExamine_;
        public int Examine
        {
            get { return roomExamine_; }
            set { roomExamine_ = value; }
        }


        private int roomId_;
        public int Id
        {
            get { return roomId_; }
            set { roomId_ = value; }
        }


        private int roomIfRecommend_;
        public int IfRecommend
        {
            get { return roomIfRecommend_; }
            set { roomIfRecommend_ = value; }
        }


        private string roomName_;
        public string Name
        {
            get { return roomName_; }
            set { roomName_ = value; }
        }


        private string roomImagePath_;
        public string ImagePath
        {
            get { return roomImagePath_; }
            set { roomImagePath_ = value; }
        }


        private int roomOwnerID_;
        public int OwnerID
        {
            get { return roomOwnerID_; }
            set { roomOwnerID_ = value; }
        }


        private string roomRecommendTime_;
        public string RecommendTime
        {
            get { return roomRecommendTime_; }
            set { roomRecommendTime_ = value; }
        }


        private decimal roomPrice_;
        public decimal RoomPrice
        {
            get { return roomPrice_; }
            set { roomPrice_ = value; }
        }


        private int roomState_;
        public int RoomState
        {
            get { return roomState_; }
            set { roomState_ = value; }
        }


        private string roomType_;
        public string RoomType
        {
            get { return roomType_; }
            set { roomType_ = value; }
        }
    }
}
