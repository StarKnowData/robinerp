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

                string[] filedName = new string[50];
                string[] paramName = new string[50];
                SqlParameter[] sqlParams = new SqlParameter[50];
                int Count = 0;



                if (model.Username != null)
                {
                    filedName[Count] = "Username";
                    paramName[Count] = "@" + filedName[Count];
                    sqlParams[Count] = new SqlParameter(paramName[Count], model.Username);
                    Count++;
                }
                if (model.Password != null)
                {
                    filedName[Count] = "Password";
                    paramName[Count] = "@" + filedName[Count];
                    sqlParams[Count] = new SqlParameter(paramName[Count], model.Password);
                    Count++;
                }
                if (model.Nickname != null)
                {
                    filedName[Count] = "Nickname";
                    paramName[Count] = "@" + filedName[Count];
                    sqlParams[Count] = new SqlParameter(paramName[Count], model.Nickname);
                    Count++;
                }
                if (model.Phone != null)
                {
                    filedName[Count] = "Phone";
                    paramName[Count] = "@" + filedName[Count];
                    sqlParams[Count] = new SqlParameter(paramName[Count], model.Phone);
                    Count++;
                }
                if (model.Address != null)
                {
                    filedName[Count] = "Address";
                    paramName[Count] = "@" + filedName[Count];
                    sqlParams[Count] = new SqlParameter(paramName[Count], model.Address);
                    Count++;
                }
                if (model.Mail != null)
                {
                    filedName[Count] = "Mail";
                    paramName[Count] = "@" + filedName[Count];
                    sqlParams[Count] = new SqlParameter(paramName[Count], model.Mail);
                    Count++;
                }
                if (model.Usertype != -999)
                {
                    filedName[Count] = "Usertype";
                    paramName[Count] = "@" + filedName[Count];
                    sqlParams[Count] = new SqlParameter(paramName[Count], model.Usertype);
                    Count++;
                }
                if (model.Action != null)
                {
                    filedName[Count] = "Action";
                    paramName[Count] = "@" + filedName[Count];
                    sqlParams[Count] = new SqlParameter(paramName[Count], model.Action);
                    Count++;
                }
                if (model.Sign != null)
                {
                    filedName[Count] = "Sign";
                    paramName[Count] = "@" + filedName[Count];
                    sqlParams[Count] = new SqlParameter(paramName[Count], model.Sign);
                    Count++;
                }

                StringBuilder strSql = new StringBuilder();
                strSql.Append("insert into Users(");
                for (int i = 0; i < Count; i++)
                {
                    strSql.Append(filedName[i]);
                    if (i != Count - 1)
                    {
                        strSql.Append(",");
                    }
                }
                strSql.Append(")values(");
                for (int i = 0; i < Count; i++)
                {
                    strSql.Append(paramName[i]);
                    if (i != Count - 1)
                    {
                        strSql.Append(",");
                    }
                }
                strSql.Append(")");



                int res = -1;
                res = sqlHelper_.ExecuteCommand(
                    strSql.ToString(),
                    CommandType.Text,
                    sqlParams
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
                "select count(*) from Users where Username=@username and Password=@password and UserType=@role";
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
            bool res = false;

            string[] filedName = new string[50];
            string[] paramName = new string[50];
            SqlParameter[] sqlParams = new SqlParameter[50];
            int Count = 0;

            if (model.Id == -999)
                return false;

            if (model.Id != -999)
            {
                filedName[Count] = "Id";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Id);
                Count++;
            }
            if (model.Username != null)
            {
                filedName[Count] = "Username";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Username);
                Count++;
            }
            if (model.Password != null)
            {
                filedName[Count] = "Password";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Password);
                Count++;
            }
            if (model.Nickname != null)
            {
                filedName[Count] = "Nickname";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Nickname);
                Count++;
            }
            if (model.Phone != null)
            {
                filedName[Count] = "Phone";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Phone);
                Count++;
            }
            if (model.Address != null)
            {
                filedName[Count] = "Address";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Address);
                Count++;
            }
            if (model.Mail != null)
            {
                filedName[Count] = "Mail";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Mail);
                Count++;
            }
            if (model.Usertype != -999)
            {
                filedName[Count] = "Usertype";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Usertype);
                Count++;
            }
            if (model.Action != null)
            {
                filedName[Count] = "Action";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Action);
                Count++;
            }
            if (model.Sign != null)
            {
                filedName[Count] = "Sign";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Sign);
                Count++;
            }

            StringBuilder strSql = new StringBuilder();
            strSql.Append("update Users set ");
            for (int i = 1; i < Count; i++)      // i begin with 0 !!!
            {
                strSql.Append(filedName[i]);
                strSql.Append("=");
                strSql.Append(paramName[i]);
                if (i != Count - 1)
                {
                    strSql.Append(",");
                }
            }
            strSql.Append(" where ");
            strSql.Append(filedName[0] + "=" + paramName[0]);


            int num = Convert.ToInt32(sqlHelper_.ExecuteCommand(
                strSql.ToString(),
                CommandType.Text,
                sqlParams
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

        public DataSet SelectList(string strWhere)
        {
            DataSet ds = null;

            ds = sqlHelper_.GetDataSet(
                "select * from Users where "+ strWhere,
                CommandType.Text,
                null
                );

            return ds;
        }

        public DataSet SelectUs(int pageSize, int currentPage)
        {
            int hasShowedPage = 0;

            hasShowedPage = currentPage - 1 >= 0 ? currentPage - 1 : 0;

            //string strSql = "select top ";
            //strSql += pageSize.ToString();
            //strSql +=
            //    " * from Users where Id not in (select top ";
            //strSql += (hasShowedPage * pageSize).ToString();
            //strSql += " Id from Users)";

            StringBuilder strSql = new StringBuilder();
            strSql.Append("SELECT TOP ");
            strSql.Append((currentPage * pageSize).ToString());
            strSql.Append(" t.* FROM (SELECT u.*, b.integral FROM users AS u, (SELECT s.userid, sum(s.content) integral FROM integral AS s WHERE 1=1 GROUP BY s.UserID) AS b WHERE u.id = b.userid ) AS t WHERE t.id NOT IN (SELECT TOP ");
            strSql.Append((hasShowedPage * pageSize).ToString());
            strSql.Append(" tt.id FROM (SELECT u.*, b.integral FROM users AS u, (SELECT s.userid, sum(s.content) integral FROM integral AS s WHERE 1=1 GROUP BY s.UserID) AS b WHERE u.id = b.userid ) AS tt)");
            DataSet ds = null;
            ds = sqlHelper_.GetDataSet(
                strSql.ToString(),
                CommandType.Text,
                null
                );

            return ds;
        }

        public int GetCount()
        {
            int res = -999;

            res = Convert.ToInt32(
                sqlHelper_.GetSingle(
                "select count(*) from Users",
                CommandType.Text,
                null
                )
                );

            return res;
        }

        public QPS.NEW.Model.Users GetUserByID(int userID)
        {
            QPS.NEW.Model.Users user = null;

            DataTable dt = sqlHelper_.GetDataTable(
                "select * from Users where Id=@id",
                CommandType.Text,
                new System.Data.SqlClient.SqlParameter[]
                {
                    new System.Data.SqlClient.SqlParameter("@id",userID)
                }
                );

            if (dt != null && dt.Rows.Count > 0)
            {
                user = new Model.Users();

                user.Id = Convert.ToInt32(dt.Rows[0]["Id"]);
                user.Username = dt.Rows[0]["Username"].ToString();
                user.Phone = dt.Rows[0]["Phone"].ToString();
                user.Address = dt.Rows[0]["Address"].ToString();
                user.Mail = dt.Rows[0]["Mail"].ToString();
            }

            return user;
        }

        public bool UpdateUs(QPS.NEW.Model.Users us)
        {
            return Update(us);
        }
    }
}
