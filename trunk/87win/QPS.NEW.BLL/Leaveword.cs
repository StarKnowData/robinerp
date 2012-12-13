using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Data.SqlClient;
using QPS.NEW.DAL;

namespace QPS.NEW.BLL
{
    public class Leaveword
    {
        private SQLHelper sqlHelper_ = null;

        public Leaveword()
        {
            sqlHelper_ = new SQLHelper(null);
        }

        public DataSet GetListLocalise(string strWhere)
        {
            DataSet ds = null;

            string strSql = 
                "select title as 标题,Content as 内容 from LeaveWord where " + strWhere;

            ds = sqlHelper_.GetDataSet(strSql, CommandType.Text, null);

            return ds;
        }

        public DataSet Select(int pageSize, int currentPage)
        {
            int hasShowedPage = 0;

            hasShowedPage = currentPage - 1 >= 0 ? currentPage - 1 : 0;

            //string strSql = "select top ";
            //strSql += pageSize.ToString();
            //strSql +=
            //    " * from Leaveword where Id not in (select top ";
            //strSql += (hasShowedPage * pageSize).ToString();
            //strSql += " Id from Leaveword)";

            StringBuilder strSql = new StringBuilder();
            strSql.Append("SELECT TOP ");
            strSql.Append((currentPage * pageSize).ToString());
            strSql.Append(" t.* FROM (SELECT o.*, u.UserName FROM Leaveword AS o, TUsers AS u WHERE u.UserId = o.Userid ) AS t ");
            strSql.Append("WHERE t.id NOT IN (SELECT TOP ");
            strSql.Append((hasShowedPage * pageSize).ToString());
            strSql.Append(" tt.id FROM (SELECT o.*, u.UserName FROM Leaveword AS o, TUsers AS u WHERE u.UserId = o.Userid ) AS tt)");


            DataSet ds = null;
            ds = sqlHelper_.GetDataSet(
                strSql.ToString(),
                CommandType.Text,
                null
                );

            return ds;
        }

        public DataSet SelectList(string strWhere)
        {
            string strSql =
                "select * from Leaveword where " + strWhere;
            DataSet ds = null;
            ds = sqlHelper_.GetDataSet(
                strSql,
                CommandType.Text,
                null
                );

            return ds;
        }

        public bool Delete(int Id)
        {
            bool res = false;

            int num =
                sqlHelper_.ExecuteCommand("delete from Leaveword where Id=@Id",
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

        public int GetCount()
        {
            int res = -999;

            res = Convert.ToInt32(
                sqlHelper_.GetSingle(
                "select count(*) from Leaveword",
                CommandType.Text,
                null
                )
                );

            return res;
        }

        public QPS.NEW.Model.Leaveword GetModel(int Id)
        {
            QPS.NEW.Model.Leaveword leaveeord = null;
            string strSql = "select * from Leaveword where Id=@id";

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
                leaveeord = new Model.Leaveword();
                leaveeord.Id = Id;
                leaveeord.UserID = Convert.ToInt32( dt.Rows[0]["UserID"]);
                leaveeord.title = dt.Rows[0]["title"].ToString();
                leaveeord.Content = dt.Rows[0]["Content"].ToString();

            }

            return leaveeord;
        }

        public int Add(QPS.NEW.Model.Leaveword model)
        {
            string[] filedName = new string[50];
            string[] paramName = new string[50];
            SqlParameter[] sqlParams = new SqlParameter[50];
            int Count = 0;



            if (model.UserID != -999)
            {
                filedName[Count] = "UserID";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.UserID);
                Count++;
            }
            if (model.title != null)
            {
                filedName[Count] = "title";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.title);
                Count++;
            }
            if (model.Content != null)
            {
                filedName[Count] = "Content";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Content);
                Count++;
            }
           

            StringBuilder strSql = new StringBuilder();
            strSql.Append("insert into Leaveword(");
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
    }
}
