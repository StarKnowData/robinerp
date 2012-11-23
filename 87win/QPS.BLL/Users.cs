using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using QPS.NEW.DAL;

namespace QPS.NEW.BLL
{
    public class Users
    {
        private QPS.NEW.Model.Users user_;

        public int Add(QPS.NEW.Model.Users model)
        {
            int checkUsername = -1;

            user_ = model;
            SQLHelper sqlHelper = new SQLHelper(null);
            checkUsername = Convert.ToInt32(
                sqlHelper.GetSingle("select count(*) from Users where Username=@username",
                CommandType.Text,
                new System.Data.SqlClient.SqlParameter[]{
                    new System.Data.SqlClient.SqlParameter("@username",user_.Username)
                }
                )
                );
            if (checkUsername != 0)
            {
                throw new Exception("Error:002-用户名已经存在");
            }
            else
            {

                string strSql = "";
                strSql += "insert into Users(Username,Password,Nickname,Phone,Address,Mail,UserType,Action,Sign) ";
                strSql += "values(@username,@password,@nickname,@phone,@address,@mail,@usertype,@action,@sign)";
                
                int res = -1;
                res = sqlHelper.ExecuteCommand(
                    strSql,
                    CommandType.Text,
                    new System.Data.SqlClient.SqlParameter[]
                {
                    new System.Data.SqlClient.SqlParameter("@username",user_.Username),
                    new System.Data.SqlClient.SqlParameter("@password",user_.Password),
                    new System.Data.SqlClient.SqlParameter("@nickname",user_.Nickname),
                    new System.Data.SqlClient.SqlParameter("@phone",user_.Phone),
                    new System.Data.SqlClient.SqlParameter("@address",user_.Address),
                    new System.Data.SqlClient.SqlParameter("@mail",user_.Mail),
                    new System.Data.SqlClient.SqlParameter("@usertype",user_.Usertype),
                    new System.Data.SqlClient.SqlParameter("@action",user_.Action),
                    new System.Data.SqlClient.SqlParameter("@sign",user_.Sign)
                }
                    );

                if (res != 1)
                {
                    throw new Exception("Error:001-查询数据库失败");
                }
            }
            return 1;
        }

        public bool Denglu(string name, string pwd)
        {
            bool res = false;
            string strSql =
                "select count(*) from Users where Username=@username and Password=@password";
            SQLHelper sqlHelper = new SQLHelper(null);
            int num =
                Convert.ToInt32(
                sqlHelper.GetSingle(strSql, CommandType.Text,
                new System.Data.SqlClient.SqlParameter[]
                {
                    new System.Data.SqlClient.SqlParameter("@username",name),
                    new System.Data.SqlClient.SqlParameter("@password",pwd)
                }
                )
                );
            if (num == 1)
            {
                res = true;
            }

            return res;
        }

        public bool Denglu(string name, string pwd, int role)
        {
            bool res = false;
            string strSql =
                "select count(*) from Users where Username=@username and Password=@password and Role=@role";
            SQLHelper sqlHelper = new SQLHelper(null);
            int num =
                Convert.ToInt32(
                sqlHelper.GetSingle(strSql, CommandType.Text,
                new System.Data.SqlClient.SqlParameter[]
                {
                    new System.Data.SqlClient.SqlParameter("@username",name),
                    new System.Data.SqlClient.SqlParameter("@password",pwd),
                    new System.Data.SqlClient.SqlParameter("@role",role)
                }
                )
                );
            if (num == 1)
            {
                res = true;
            }

            return res;
        }
    }
}
