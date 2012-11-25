using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;
using QPS.NEW.DAL;

namespace QPS.NEW.BLL
{
    public class Integral
    {
        private SQLHelper sqlHelper_;

        public Integral()
        {
            sqlHelper_ = new SQLHelper(null);
        }

        public QPS.NEW.Model.Integral GetModel(int Id)
        {
            QPS.NEW.Model.Integral integral = null;
            string strSql = "select * from Integral where Id=@id";

            DataTable dt = sqlHelper_.GetDataTable(
                strSql,
                CommandType.Text,
                new SqlParameter[]
                {
                    new SqlParameter("@id",Id)
                }
                );

            if (dt != null && dt.Rows.Count > 0)
            {
                integral = new Model.Integral();
                integral.Id = Id;
                integral.UserID = dt.Rows[0]["UserID"].ToString();
                integral.Content = Convert.ToInt32(dt.Rows[0]["Content"]);
                integral.CreateTime = Convert.ToDateTime(dt.Rows[0]["CreateTime"]);
                integral.RoomId = Convert.ToInt32(dt.Rows[0]["RoomId"]);
                integral.OrderId = Convert.ToInt32(dt.Rows[0]["OrderId"]);
            }

            return integral;
        }

        public bool Update(QPS.NEW.Model.Integral model)
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
            if (model.UserID != null)
            {
                filedName[Count] = "UserID";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.UserID);
                Count++;
            }
            if (model.Content != null)
            {
                filedName[Count] = "Content";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Content);
                Count++;
            }
            if (model.CreateTime != null)
            {
                filedName[Count] = "CreateTime";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.CreateTime);
                Count++;
            }
            if (model.RoomId != null)
            {
                filedName[Count] = "RoomId";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.RoomId);
                Count++;
            }
            if (model.OrderId != null)
            {
                filedName[Count] = "OrderId";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.OrderId);
                Count++;
            }


            StringBuilder strSql = new StringBuilder();
            strSql.Append("update Integral set ");
            for (int i = 1; i < Count; i++)
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

        public DataSet GetListlocalize(string strWhere)
        {
            DataSet ds = null;
            string strSql = "select * from Integral where " + strWhere;

            ds = sqlHelper_.GetDataSet(strSql, CommandType.Text, null);

            return ds;
        }

        public DataSet GetSum(int userId)
        {
            DataSet ds = null;
            string strSql = "select sum(Content) from Integral where UserID=@UserID";

            ds = sqlHelper_.GetDataSet(strSql, CommandType.Text,
                new SqlParameter[]{
                    new SqlParameter("@UserID",userId)
                }
                );

            return ds;
        }

        public DataSet GetList(string strWhere)
        {
            DataSet ds = null;
            ds = sqlHelper_.GetDataSet("select * from Integral where " + strWhere,
                CommandType.Text,
                null);

            return ds;
        }

        public bool Delete(int Id)
        {
            bool res = false;

            int num =
                sqlHelper_.ExecuteCommand("delete from Integral where Id=@Id",
                CommandType.Text,
                new SqlParameter[]
                {
                    new SqlParameter("@Id",Id)
                }
                );
            if (num == 1)
                res = true;

            return res;
        }

        public bool DeleteByUid(int userId)
        {
            bool res = false;

            int num =
                sqlHelper_.ExecuteCommand("delete from Integral where UserID=@Id",
                CommandType.Text,
                new SqlParameter[]
                {
                    new SqlParameter("@Id",userId)
                }
                );
            if (num >= 0)
                res = true;

            return res;
        }

        public int Add(QPS.NEW.Model.Integral model)
        {
            string[] filedName = new string[50];
            string[] paramName = new string[50];
            SqlParameter[] sqlParams = new SqlParameter[50];
            int Count = 0;



            if (model.UserID != null)
            {
                filedName[Count] = "UserID";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.UserID);
                Count++;
            }
            if (model.Content != null)
            {
                filedName[Count] = "Content";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Content);
                Count++;
            }
            if (model.CreateTime != null)
            {
                filedName[Count] = "CreateTime";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.CreateTime);
                Count++;
            }
            if (model.RoomId != null)
            {
                filedName[Count] = "RoomId";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.RoomId);
                Count++;
            }
            if (model.OrderId != null)
            {
                filedName[Count] = "OrderId";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.OrderId);
                Count++;
            }



            StringBuilder strSql = new StringBuilder();
            strSql.Append("insert into Integral(");
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

            return 1;
        }

        public DataSet Select(int pageSize, int currentPage)
        {
            int hasShowedPage = 0;

            hasShowedPage = currentPage - 1 >= 0 ? currentPage - 1 : 0;

            //string strSql = "select top ";
            //strSql += pageSize.ToString();
            //strSql +=
            //    " * from Integral where Id not in (select top ";
            //strSql += (hasShowedPage * pageSize).ToString();
            //strSql += " Id from Integral)";

            StringBuilder strSql = new StringBuilder();
            strSql.Append("SELECT TOP ");
            strSql.Append((currentPage * pageSize).ToString());
            strSql.Append(" t.* FROM (SELECT u.Id, u.Username, b.integral FROM users AS u, (SELECT s.userid, sum(s.content) integral FROM integral AS s WHERE 1=1 GROUP BY s.UserID) AS b WHERE u.id = b.userid ) AS t");
            strSql.Append(" WHERE t.id NOT IN (SELECT TOP ");
            strSql.Append((hasShowedPage * pageSize).ToString());
            strSql.Append(" tt.id FROM (SELECT u.Id, u.Username, b.integral FROM users AS u, (SELECT s.userid, sum(s.content) integral FROM integral AS s WHERE 1=1 GROUP BY s.UserID) AS b WHERE u.id = b.userid ) AS tt)");


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
                "select count(*) from Integral",
                CommandType.Text,
                null
                )
                );

            return res;
        }

        public DataSet SelectByName(string strWhere)
        {
            DataSet ds = null;
            string strSql = "select * from Integral where " + strWhere;
            ds = sqlHelper_.GetDataSet
                (
                strSql,
                CommandType.Text,
                null
                );

            return ds;
        }

        public bool UpdateContent(QPS.NEW.Model.Integral model)
        {
            bool res = false;

            int num = Convert.ToInt32(sqlHelper_.ExecuteCommand(
               "update Integral set Content=@content",
               CommandType.Text,
               new SqlParameter[]
               {
                   new SqlParameter("@content",model.Content)
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

        public DataSet SelectByJfxq(string strWhere)
        {
            DataSet ds = null;
            string strSql =
                "select * from Intrgral where " + strWhere + " order by Id ASC";

            ds = sqlHelper_.GetDataSet
                (
                strSql,
                CommandType.Text,
                null
                );

            return ds;
        }
    }
}
