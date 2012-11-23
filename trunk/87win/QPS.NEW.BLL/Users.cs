using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;
using QPS.NEW.DAL;
using QPS.NEW.Model;

namespace QPS.NEW.BLL
{
    public class Users
    {
        private QPS.NEW.Model.Users user_;
        private SQLHelper sqlHelper_;

        public Users()
        {
            sqlHelper_ = new SQLHelper(null);
        }

        public int Add(QPS.NEW.Model.Users model)
        {
            int checkUsername = -1;

            user_ = model;
            checkUsername = Convert.ToInt32(
                sqlHelper_.GetSingle("select count(*) from Users where Username=@username",
                CommandType.Text,
                new System.Data.SqlClient.SqlParameter[]{
                    new System.Data.SqlClient.SqlParameter("@username",user_.Username)
                }
                )
                );
            if (checkUsername != 0)
            {
                throw new Exception("Error:用户名已经存在");
            }
            else
            {

                string strSql = "";
                strSql += "insert into Users(Username,Password,Nickname,Phone,Address,Mail,UserType,Action,Sign) ";
                strSql += "values(@username,@password,@nickname,@phone,@address,@mail,@usertype,@action,@sign)";
                
                int res = -1;
                res = sqlHelper_.ExecuteCommand(
                    strSql,
                    CommandType.Text,
                    new System.Data.SqlClient.SqlParameter[]
                {
                    new SqlParameter("@username",user_.Username),
                    new SqlParameter("@password",user_.Password),
                    new SqlParameter("@nickname",user_.Nickname),
                    new SqlParameter("@phone",user_.Phone),
                    new SqlParameter("@address",user_.Address),
                    new SqlParameter("@mail",user_.Mail),
                    new SqlParameter("@usertype",user_.Usertype),
                    new SqlParameter("@action",user_.Action),
                    new SqlParameter("@sign",user_.Sign)
                }
                    );

                if (res != 1)
                {
                    throw new Exception("Error:写入数据库失败");
                }
            }
            return 1;
        }

        public bool Denglu(string name, string pwd)
        {
            bool res = false;
            string strSql =
                "select count(*) from Users where Username=@username and Password=@password";
            int num =
                Convert.ToInt32(
                sqlHelper_.GetSingle(strSql, CommandType.Text,
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
            int num =
                Convert.ToInt32(
                sqlHelper_.GetSingle(strSql, CommandType.Text,
                new System.Data.SqlClient.SqlParameter[]
                {
                    new SqlParameter("@username",name),
                    new SqlParameter("@password",pwd),
                    new SqlParameter("@role",role)
                }
                )
                );
            if (num == 1)
            {
                res = true;
            }

            return res;
        }

        public DataSet GetList(string strWhere)
        {
            DataSet ds = null;
            string strSql =
                "select * from Users where " + strWhere;

            ds = sqlHelper_.GetDataSet(strSql, CommandType.Text, null);

            return ds;
        }

        public QPS.NEW.Model.Users GetModel(int Id)
        {
            QPS.NEW.Model.Users user = null;

            DataTable dt = sqlHelper_.GetDataTable(
                "select * from Users where Id=@id",
                CommandType.Text,
                new System.Data.SqlClient.SqlParameter[]
                {
                    new System.Data.SqlClient.SqlParameter("@id",Id)
                }
                );

            if (dt!=null && dt.Rows.Count > 0)
            {
                user = new Model.Users();

                user.Id = Convert.ToInt32(dt.Rows[0]["Id"]);
                user.Username = dt.Rows[0]["Username"].ToString();
                user.Password = dt.Rows[0]["Password"].ToString();
                user.Nickname = dt.Rows[0]["Nickname"].ToString();
                user.Phone = dt.Rows[0]["Phone"].ToString();
                user.Address = dt.Rows[0]["Address"].ToString();
                user.Mail = dt.Rows[0]["Mail"].ToString();
                user.Usertype = Convert.ToInt32(dt.Rows[0]["Usertype"]);
                user.Action = dt.Rows[0]["Action"].ToString();
                user.Sign = dt.Rows[0]["Sign"].ToString();
            }

            return user;
        }

        public bool Update(QPS.NEW.Model.Users model)
        {
            string strSql = "";
            bool res = false;

            strSql = "update Users set Username=@username,Password=@password,Nickname=@nickname,";
            strSql += "Phone=@phone,Address=@address,Mail=@mail,Usertype=@usertype,";
            strSql += "Action=@action,Sign=@sign ";
            strSql += " where Id=@id";

            int num = Convert.ToInt32(sqlHelper_.ExecuteCommand(
                strSql,
                CommandType.Text,
                new SqlParameter[]{
                    new SqlParameter("@username",model.Username),
                    new SqlParameter("@password",model.Password),
                    new SqlParameter("@nickname",model.Nickname),
                    new SqlParameter("@phone",model.Phone),
                    new SqlParameter("@address",model.Address),
                    new SqlParameter("@mail",model.Mail),
                    new SqlParameter("@usertype",model.Usertype),
                    new SqlParameter("@action",model.Action),
                    new SqlParameter("@sign",model.Sign),
                    new SqlParameter("@id",model.Id)
                }
                ));
            if (num != 1)
            {
                throw new Exception("Error:更新数据库失败");
            }
            else
            {
                res = true;
            }

            return res;
        }
    }
}
