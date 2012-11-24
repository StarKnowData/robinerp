using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace QPS.NEW.Model
{
    public class Enterprise
    {
        public Enterprise()
        {
            enterpriseId_ = -999;
            enterpriseIfChecked_ = -999;
        }

        private int enterpriseId_;

        public int Id
        {
            get { return enterpriseId_; }
            set { enterpriseId_ = value; }
        }
        private string enterpriseAddress_;

        public string Address
        {
            get { return enterpriseAddress_; }
            set { enterpriseAddress_ = value; }
        }
        private int enterpriseIfChecked_;

        public int IfChecked
        {
            get { return enterpriseIfChecked_; }
            set { enterpriseIfChecked_ = value; }
        }
        private string enterpriseMail_;

        public string Mail
        {
            get { return enterpriseMail_; }
            set { enterpriseMail_ = value; }
        }
        private string enterpriseNickname_;

        public string Nickname
        {
            get { return enterpriseNickname_; }
            set { enterpriseNickname_ = value; }
        }
        private string enterprisePassword_;

        public string Password
        {
            get { return enterprisePassword_; }
            set { enterprisePassword_ = value; }
        }
        private string enterprisePhone_;

        public string Phone
        {
            get { return enterprisePhone_; }
            set { enterprisePhone_ = value; }
        }
        private string enterpriseName_;

        public string Username
        {
            get { return enterpriseName_; }
            set { enterpriseName_ = value; }
        }


    }
}
