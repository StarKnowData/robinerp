using System;
using System.Collections.Generic;
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
            int res = -1;

            user_ = model;
            checkUsername = Convert.ToInt32(
                sqlHelper_.GetSingle("select count(*) from TUsers where UserName=@username",
                CommandType.Text,
                new System.Data.SqlClient.SqlParameter[]{
                    new System.Data.SqlClient.SqlParameter("@username",user_.Username)
                }
                )
                );
            if (checkUsername != 0)
            {
                return -1;
            }
            else
            {

                string[] filedName = new string[50];
                string[] paramName = new string[50];
                SqlParameter[] sqlParams = new SqlParameter[50];
                int Count = 0;

                int userId = Convert.ToInt32(sqlHelper_.GetSingle(
                            "select Max(UserID) from TUsers",
                        CommandType.Text,
                        new SqlParameter[]
                         {
                             new SqlParameter("@username",model.Username)
                         }
                        )) + 1;

                filedName[Count] = "UserID";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], userId);
                Count++;

                if (model.Username != null)
                {
                    filedName[Count] = "UserName";
                    paramName[Count] = "@" + filedName[Count];

                    sqlParams[Count] = new SqlParameter(paramName[Count], model.Username);
                    Count++;
                }
                if (model.Password != null)
                {
                    filedName[Count] = "Pass";
                    paramName[Count] = "@" + filedName[Count];
                    string md5Pwd = MD5Helper.Encode(model.Password);
                    sqlParams[Count] = new SqlParameter(paramName[Count], md5Pwd);
                    Count++;
                }
                if (model.Nickname != null)
                {
                    filedName[Count] = "NickName";
                    paramName[Count] = "@" + filedName[Count];
                    sqlParams[Count] = new SqlParameter(paramName[Count], model.Nickname);
                    Count++;
                }

                StringBuilder strSql = new StringBuilder();
                strSql.Append("insert into TUsers(");
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

                res = sqlHelper_.ExecuteCommand(
                    strSql.ToString(),
                    CommandType.Text,
                    sqlParams
                    );

                if (res != 1)
                {
                    return -2;
                }
                else
                {

                    // 初始化数组
                    for (int i = 0; i < 50; i++)
                    {
                        filedName[i] = null;
                        paramName[i] = null;
                        sqlParams[i] = null;
                    }
                    Count = 0;

                    filedName[Count] = "UserID";
                    paramName[Count] = "@" + filedName[Count];
                    sqlParams[Count] = new SqlParameter(paramName[Count], userId);
                    Count++;

                    if (model.Phone != null)
                    {
                        filedName[Count] = "PhoneNum";
                        paramName[Count] = "@" + filedName[Count];
                        sqlParams[Count] = new SqlParameter(paramName[Count], model.Phone);
                        Count++;
                    }

                    if (model.Usertype != -999)
                    {
                        filedName[Count] = "UserType";
                        paramName[Count] = "@" + filedName[Count];
                        sqlParams[Count] = new SqlParameter(paramName[Count], model.Usertype);
                        Count++;
                    }

                    strSql = new StringBuilder();
                    strSql.Append("insert into TUserInfo(");
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



                    res = -1;
                    res = sqlHelper_.ExecuteCommand(
                        strSql.ToString(),
                        CommandType.Text,
                        sqlParams
                        );

                    if (res != 1)
                    {
                        return -2;
                    }

                    if (model.Mail != null)
                    {
                        res = -1;

                        res = sqlHelper_.ExecuteCommand(
                            "insert into Web_Users(UserID,Email,Phone,Address)values(@userid,@email,@phone,@address)",
                            CommandType.Text,
                            new SqlParameter[]
                            {
                                new SqlParameter("@userid",userId),
                                new SqlParameter("@email",model.Mail),
                                new SqlParameter("@phone",model.Phone),
                                new SqlParameter("@address",model.Address)
                            }
                            );
                        if (res != 1)
                        {
                            return -2;
                        }
                    }


                }
            }
            return 1;
        }

        public bool Denglu(string name, string pwd)
        {
            bool res = false;

            string strSql =
                "select count(*) from TUsers where UserName=@username and Pass=@password";
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
                "select count(*) from TUserInfo where UserType=@role and UserID=(select UserID from TUsers where UserName=@username and Pass=@password)";
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



        public bool Update(QPS.NEW.Model.Users model)
        {
            string[] filedName = new string[50];
            string[] paramName = new string[50];
            SqlParameter[] sqlParams = new SqlParameter[50];
            int Count = 0;

            if (model.Id == -999)
                return false;

            if (model.Id != -999)
            {
                filedName[Count] = "UserID";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Id);
                Count++;
            }
            if (model.Username != null)
            {
                filedName[Count] = "UserName";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Username);
                Count++;
            }
            if (model.Password != null)
            {
                filedName[Count] = "Pass";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Password);
                Count++;
            }
            if (model.Nickname != null)
            {
                filedName[Count] = "NickName";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Nickname);
                Count++;
            }
            StringBuilder strSql = new StringBuilder();
            strSql.Append("update TUsers set ");
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
                return false;
            }



            strSql = new StringBuilder();
            for (int i = 0; i < 50; i++)
            {
                filedName[i] = null;
                paramName[i] = null;
                sqlParams[i] = null;
            }
            Count = 0;

            filedName[Count] = "UserID";
            paramName[Count] = "@" + filedName[Count];
            sqlParams[Count] = new SqlParameter(paramName[Count], model.Id);
            Count++;

            if (model.Phone != null)
            {
                filedName[Count] = "PhoneNum";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Phone);
                Count++;
            }
            if (model.Usertype != -999)
            {
                filedName[Count] = "Usertype";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Usertype);
                Count++;
            }

            strSql.Append("update TUserinfo set ");
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


            num = Convert.ToInt32(sqlHelper_.ExecuteCommand(
                strSql.ToString(),
                CommandType.Text,
                sqlParams
                ));
            if (num != 1)
                return false;


            strSql = new StringBuilder();
            for (int i = 0; i < 50; i++)
            {
                filedName[i] = null;
                paramName[i] = null;
                sqlParams[i] = null;
            }
            Count = 0;

            filedName[Count] = "UserID";
            paramName[Count] = "@" + filedName[Count];
            sqlParams[Count] = new SqlParameter(paramName[Count], model.Id);
            Count++;

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
                filedName[Count] = "Email";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Mail);
                Count++;
            }


            strSql.Append("update Web_Users set ");
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


            num = Convert.ToInt32(sqlHelper_.ExecuteCommand(
                strSql.ToString(),
                CommandType.Text,
                sqlParams
                ));

            if (num != 1)
            {
                return false;
            }

            return true;
        }

        public DataSet GetList(string strUserName)
        {

            int userid;
            DataTable dt = new DataTable();
            DataColumn dc1 = dt.Columns.Add("UserID",typeof(int));
            DataColumn dc2 = dt.Columns.Add("UserName",typeof(string));
            DataColumn dc3 = dt.Columns.Add("Pass", typeof(string));
            DataColumn dc4 = dt.Columns.Add("NickName", typeof(string));
            DataColumn dc5 = dt.Columns.Add("UserType", typeof(int));
            DataColumn dc6 = dt.Columns.Add("Email", typeof(string));
            DataColumn dc7 = dt.Columns.Add("Phone", typeof(string));
            DataColumn dc8 = dt.Columns.Add("Address", typeof(string));

            DataRow dr = dt.NewRow();

            DataTable dtRes = sqlHelper_.GetDataTable(
                "select * from TUsers where UserName=@username",
                CommandType.Text,
                new SqlParameter[]{new SqlParameter("@username",strUserName)}
                );

            if(dtRes.Rows.Count<=0)
                return null;

            userid=Convert.ToInt32( dtRes.Rows[0]["UserID"]);
            dr["UserID"]=userid;
            dr["UserName"]=dtRes.Rows[0]["UserName"].ToString();
            dr["Pass"]=dtRes.Rows[0]["Pass"].ToString();
            dr["NickName"]=dtRes.Rows[0]["NickName"].ToString();

            dtRes=null;
            dtRes=sqlHelper_.GetDataTable(
                "select i.UserType,w.Phone,w.Email,w.Address from TUserInfo as i,Web_Users as w where w.UserID=i.UserID and w.UserID=@userid",
                CommandType.Text,
                new SqlParameter[]{new SqlParameter("@userid",userid)}
                );

            if(dtRes!=null && dtRes.Rows.Count>0)
            {
                dr["UserType"]=Convert.ToInt32( dtRes.Rows[0]["UserType"]);
                dr["Phone"]=dtRes.Rows[0]["Phone"].ToString();
                dr["Email"]=dtRes.Rows[0]["Email"].ToString();
                dr["Address"]=dtRes.Rows[0]["Address"].ToString();
            }

            dt.Rows.Add(dr);
            DataSet ds = new DataSet();
            ds.Tables.Add(dt);

            return ds;
        }

        public DataSet GetList(int userID)
        {
            DataTable dt = new DataTable();
            DataColumn dc1 = dt.Columns.Add("UserID", typeof(int));
            DataColumn dc2 = dt.Columns.Add("UserName", typeof(string));
            DataColumn dc3 = dt.Columns.Add("Pass", typeof(string));
            DataColumn dc4 = dt.Columns.Add("NickName", typeof(string));
            DataColumn dc5 = dt.Columns.Add("UserType", typeof(int));
            DataColumn dc6 = dt.Columns.Add("Email", typeof(string));
            DataColumn dc7 = dt.Columns.Add("Phone", typeof(string));
            DataColumn dc8 = dt.Columns.Add("Address", typeof(string));

            DataRow dr = dt.NewRow();

            DataTable dtRes = sqlHelper_.GetDataTable(
                "select * from TUsers where UserID=@userid",
                CommandType.Text,
                new SqlParameter[] { new SqlParameter("@userid", userID) }
                );

            if (dtRes.Rows.Count <= 0)
                return null;


            dr["UserID"] = userID;
            dr["UserName"] = dtRes.Rows[0]["UserName"].ToString();
            dr["Pass"] = dtRes.Rows[0]["Pass"].ToString();
            dr["NickName"] = dtRes.Rows[0]["NickName"].ToString();

            dtRes = null;
            dtRes = sqlHelper_.GetDataTable(
                "select i.UserType,w.Phone,w.Email,w.Address from TUserInfo as i,Web_Users as w where w.UserID=i.UserID and w.UserID=@userid",
                CommandType.Text,
                new SqlParameter[] { new SqlParameter("@userid", userID) }
                );

            if (dtRes != null && dtRes.Rows.Count > 0)
            {
                dr["UserType"] = Convert.ToInt32(dtRes.Rows[0]["UserType"]);
                dr["Phone"] = dtRes.Rows[0]["Phone"].ToString();
                dr["Email"] = dtRes.Rows[0]["Email"].ToString();
                dr["Address"] = dtRes.Rows[0]["Address"].ToString();
            }

            dt.Rows.Add(dr);

            DataSet ds = new DataSet();
            ds.Tables.Add(dt);

            return ds;
        }

        public DataSet GetList(string userName, string nickName)
        {
            int userid;
            DataTable dt = new DataTable();
            DataColumn dc1 = dt.Columns.Add("UserID", typeof(int));
            DataColumn dc2 = dt.Columns.Add("UserName", typeof(string));
            DataColumn dc3 = dt.Columns.Add("Pass", typeof(string));
            DataColumn dc4 = dt.Columns.Add("NickName", typeof(string));
            DataColumn dc5 = dt.Columns.Add("UserType", typeof(int));
            DataColumn dc6 = dt.Columns.Add("Email", typeof(string));
            DataColumn dc7 = dt.Columns.Add("Phone", typeof(string));
            DataColumn dc8 = dt.Columns.Add("Address", typeof(string));

            DataRow dr = dt.NewRow();

            DataTable dtRes = sqlHelper_.GetDataTable(
                "select * from TUsers where UserName=@username and NickName=@nickname",
                CommandType.Text,
                new SqlParameter[] { new SqlParameter("@username", userName),
                new SqlParameter("@nickname",nickName)
                }
                );

            if (dtRes.Rows.Count <= 0)
                return null;

            userid = Convert.ToInt32(dtRes.Rows[0]["UserID"]);
            dr["UserID"] = userid;
            dr["UserName"] = dtRes.Rows[0]["UserName"].ToString();
            dr["Pass"] = dtRes.Rows[0]["Pass"].ToString();
            dr["NickName"] = dtRes.Rows[0]["NickName"].ToString();

            dtRes = null;
            dtRes = sqlHelper_.GetDataTable(
                "select i.UserType,w.Phone,w.Email,w.Address from TUserInfo as i,Web_Users as w where w.UserID=i.UserID and w.UserID=@userid",
                CommandType.Text,
                new SqlParameter[] { new SqlParameter("@userid", userid) }
                );

            if (dtRes != null && dtRes.Rows.Count > 0)
            {
                dr["UserType"] = Convert.ToInt32(dtRes.Rows[0]["UserType"]);
                dr["Phone"] = dtRes.Rows[0]["Phone"].ToString();
                dr["Email"] = dtRes.Rows[0]["Email"].ToString();
                dr["Address"] = dtRes.Rows[0]["Address"].ToString();
            }

            dt.Rows.Add(dr);

            DataSet ds = new DataSet();
            ds.Tables.Add(dt);

            return ds;
        }

        public DataSet SelectList(string phone)
        {
            int userid;
            DataTable dt = new DataTable();
            DataColumn dc1 = dt.Columns.Add("UserID", typeof(int));
            DataColumn dc2 = dt.Columns.Add("UserName", typeof(string));
            DataColumn dc3 = dt.Columns.Add("Pass", typeof(string));
            DataColumn dc4 = dt.Columns.Add("NickName", typeof(string));
            DataColumn dc5 = dt.Columns.Add("UserType", typeof(int));
            DataColumn dc6 = dt.Columns.Add("Email", typeof(string));
            DataColumn dc7 = dt.Columns.Add("Phone", typeof(string));
            DataColumn dc8 = dt.Columns.Add("Address", typeof(string));

            DataRow dr = dt.NewRow();

            DataTable dtRes = sqlHelper_.GetDataTable(
                "select * from TUserInfo where PhoneNum=@phone",
                CommandType.Text,
                new SqlParameter[] { new SqlParameter("@phone", phone) }
                );

            if (dtRes.Rows.Count <= 0)
                return null;

            userid = Convert.ToInt32(dtRes.Rows[0]["UserID"]);
            dr["UserID"] = userid;
            dr["UserName"] = dtRes.Rows[0]["UserName"].ToString();
            dr["Pass"] = dtRes.Rows[0]["Pass"].ToString();
            dr["NickName"] = dtRes.Rows[0]["NickName"].ToString();

            dtRes = null;
            dtRes = sqlHelper_.GetDataTable(
                "select i.UserType,w.Phone,w.Email,w.Address from TUserInfo as i,Web_Users as w where w.UserID=i.UserID and w.UserID=@userid",
                CommandType.Text,
                new SqlParameter[] { new SqlParameter("@userid", userid) }
                );

            if (dtRes != null && dtRes.Rows.Count > 0)
            {
                dr["UserType"] = Convert.ToInt32(dtRes.Rows[0]["UserType"]);
                dr["Phone"] = dtRes.Rows[0]["Phone"].ToString();
                dr["Email"] = dtRes.Rows[0]["Email"].ToString();
                dr["Address"] = dtRes.Rows[0]["Address"].ToString();
            }

            dt.Rows.Add(dr);
            DataSet ds = new DataSet();
            ds.Tables.Add(dt);

            return ds;
        }

        public int SelectUser(string userName)
        {


            int num=-1;
            num= Convert.ToInt32(
                sqlHelper_.GetSingle(
                "select count(*) from TUsers where UserName=@username",
                CommandType.Text,
                new SqlParameter[] { new SqlParameter("@username", userName) }
                )
                );

            return num;
        }


        public QPS.NEW.Model.Users GetModel(int userID)
        {
            QPS.NEW.Model.Users u = new Model.Users();


            DataTable dtRes = sqlHelper_.GetDataTable(
                "select * from TUsers where UserID=@userid",
                CommandType.Text,
                new SqlParameter[] { new SqlParameter("@userid", userID) }
                );

            if (dtRes.Rows.Count <= 0)
                return null;


            u.Id = userID;
            u.Username = dtRes.Rows[0]["UserName"].ToString();
            u.Password = dtRes.Rows[0]["Pass"].ToString();
            u.Nickname = dtRes.Rows[0]["NickName"].ToString();

            dtRes = null;
            dtRes = sqlHelper_.GetDataTable(
                "select i.UserType,w.Phone,w.Email,w.Address from TUserInfo as i,Web_Users as w where w.UserID=i.UserID and w.UserID=@userid",
                CommandType.Text,
                new SqlParameter[] { new SqlParameter("@userid", userID) }
                );

            if (dtRes != null && dtRes.Rows.Count > 0)
            {
                u.Usertype =Convert.ToInt32( dtRes.Rows[0]["UserType"] );
                u.Phone = dtRes.Rows[0]["Phone"].ToString();
                u.Mail = dtRes.Rows[0]["Email"].ToString();
                u.Address = dtRes.Rows[0]["Address"].ToString();
            }

            return u;
        }


        public DataSet SelectUs(int pageSize, int currentPage)
        {
            int hasShowedPage = 0;

            hasShowedPage = currentPage - 1 >= 0 ? currentPage - 1 : 0;


            StringBuilder strSql = new StringBuilder();
            strSql.Append("select top ");
            strSql.Append((currentPage * pageSize).ToString());
            strSql.Append(" u.UserID,u.UserName,(i.BankMoney+i.WalletMoney)/10000 as TotalMoney,i.PhoneNum from TUsers as u INNER JOIN TUserInfo as i ON u.UserID=i.UserID and u.UserID not in(select top ");
            strSql.Append((hasShowedPage * pageSize).ToString());
            strSql.Append(" u.UserID from TUsers as u INNER JOIN TUserInfo as i ON u.UserID=i.UserID)");
            
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
                "select count(*) from TUsers",
                CommandType.Text,
                null
                )
                );

            return res;
        }



        public bool UpdateUs(QPS.NEW.Model.Users us)
        {
            return Update(us);
        }
    }
}
