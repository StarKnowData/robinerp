using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;
using QPS.NEW.DAL;

namespace QPS.NEW.BLL
{
    public class Enterprise
    {
        private QPS.NEW.Model.Enterprise enterprise_;
        private SQLHelper sqlHelper_;

        public Enterprise()
        {
            sqlHelper_=new SQLHelper(null);
        }

        public int Add(QPS.NEW.Model.Enterprise model)
        {

            int checkUsername = -1;

            enterprise_ = model;
            checkUsername = Convert.ToInt32(
                sqlHelper_.GetSingle("select count(*) from Enterprise where Username=@username",
                CommandType.Text,
                new System.Data.SqlClient.SqlParameter[]{
                    new System.Data.SqlClient.SqlParameter("@username",enterprise_.Username)
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
                strSql += "insert into Enterprise(Username,Password,Nickname,Phone,Address,Mail,IfChecked) ";
                strSql += "values(@username,@password,@nickname,@phone,@address,@mail,@ifchecked)";

                int res = -1;
                res = sqlHelper_.ExecuteCommand(
                    strSql,
                    CommandType.Text,
                    new System.Data.SqlClient.SqlParameter[]
                {
                    new SqlParameter("@username",enterprise_.Username),
                    new SqlParameter("@password",enterprise_.Password),
                    new SqlParameter("@nickname",enterprise_.Nickname),
                    new SqlParameter("@phone",enterprise_.Phone),
                    new SqlParameter("@address",enterprise_.Address),
                    new SqlParameter("@mail",enterprise_.Mail),
                    new SqlParameter("@ifchecked",enterprise_.IfChecked)
                }
                    );

                if (res != 1)
                {
                    throw new Exception("Error:001-查询数据库失败");
                }
            }
            return 1;
        }

        public DataSet GetList(string strWhere)
        {
            DataSet ds = null;
            sqlHelper_ = new SQLHelper(null);
            string strSql = 
                "select * from Enterprise where " + strWhere;

            ds=sqlHelper_.GetDataSet(strSql, CommandType.Text, null);

            return ds;
        }


        public QPS.NEW.Model.Enterprise GetModel(int Id)
        {
            QPS.NEW.Model.Enterprise user = null;

            DataTable dt = sqlHelper_.GetDataTable(
                "select * from Enterprise where Id=@id",
                CommandType.Text,
                new System.Data.SqlClient.SqlParameter[]
                {
                    new SqlParameter("@id",Id)
                }
                );

            if (dt != null && dt.Rows.Count > 0)
            {
                user = new Model.Enterprise();

                user.Id = Convert.ToInt32(dt.Rows[0]["Id"]);
                user.Username = dt.Rows[0]["Username"].ToString();
                user.Password = dt.Rows[0]["Password"].ToString();
                user.Nickname = dt.Rows[0]["Nickname"].ToString();
                user.Phone = dt.Rows[0]["Phone"].ToString();
                user.Address = dt.Rows[0]["Address"].ToString();
                user.Mail = dt.Rows[0]["Mail"].ToString();
                user.IfChecked = Convert.ToInt32(dt.Rows[0]["IfChecked"]);
            }

            return user;
        }

        public bool Update(QPS.NEW.Model.Enterprise model)
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
            if (model.IfChecked != -999)
            {
                filedName[Count] = "IfChecked";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.IfChecked);
                Count++;
            }
            

            StringBuilder strSql = new StringBuilder();
            strSql.Append("update Enterprise set ");
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
    }
}
