using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace QPS.NEW.Model
{
    [Serializable]
    public class Users
    {
        private int userID_;

        public int Id
        {
            get { return userID_; }
            set { userID_ = value; }
        }


        private int userType_;

        public int Usertype
        {
            get { return userType_; }
            set { userType_ = value; }
        }



        private string userName_;

        public string Username
        {
            get { return userName_; }
            set { userName_ = value; }
        }
        private string userNickname_;

        public string Nickname
        {
            get { return userNickname_; }
            set { userNickname_ = value; }
        }



        private string userPassword_;

        public string Password
        {
            get { return userPassword_; }
            set { userPassword_ = value; }
        }
        private string userAction_;

        public string Action
        {
            get { return userAction_; }
            set { userAction_ = value; }
        }



        private string userMail_;

        public string Mail
        {
            get { return userMail_; }
            set { userMail_ = value; }
        }


        private string userAddress_;

        public string Address
        {
            get { return userAddress_; }
            set { userAddress_ = value; }
        }



        private string userSign_;

        public string Sign
        {
            get { return userSign_; }
            set { userSign_ = value; }
        }



        private string userPhone_;

        public string Phone
        {
            get { return userPhone_; }
            set { userPhone_ = value; }
        }

        

    }
}
