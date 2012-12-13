using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Data.SqlClient;
using QPS.NEW.DAL;

namespace QPS.NEW.BLL
{
    public class Trends
    {
        private SQLHelper sqlHelper_;

        public Trends()
        {
            sqlHelper_ = new SQLHelper(null);
        }

        public DataSet GetTopList(int num)
        {
            DataSet ds = null;
            string strsql = "select top 6 Id,Title,time from Trends";

            ds = sqlHelper_.GetDataSet(strsql, CommandType.Text, null);

            return ds;
        }

        public DataSet GetList()
        {
            DataSet ds = null;
            string strsql = "select Id,Title,time from Trends";

            ds = sqlHelper_.GetDataSet(strsql, CommandType.Text, null);

            return ds;
        }

        public DataSet GetList(string strWhere)
        {
            DataSet ds = null;
            string strsql = "select Title,time,Content from Trends where ";

            strsql += strWhere;

            ds = sqlHelper_.GetDataSet(strsql, CommandType.Text, null);

            return ds;
        }

        public int Add(QPS.NEW.Model.Trends model)
        {
            string[] filedName = new string[50];
            string[] paramName = new string[50];
            SqlParameter[] sqlParams = new SqlParameter[50];
            int Count = 0;



            if (model.Title != null)
            {
                filedName[Count] = "Title";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Title);
                Count++;
            }
            if (model.Content != null)
            {
                filedName[Count] = "Content";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Content);
                Count++;
            }
            if (model.Time != null)
            {
                filedName[Count] = "time";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Time);
                Count++;
            }
           

            StringBuilder strSql = new StringBuilder();
            strSql.Append("insert into Trends(");
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

            string strSql = "select top ";
            strSql += pageSize.ToString();
            strSql +=
                " * from Trends where Id not in (select top ";
            strSql += (hasShowedPage * pageSize).ToString();
            strSql += " Id from Trends)";

            DataSet ds = null;
            ds = sqlHelper_.GetDataSet(
                strSql,
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
                "select count(*) from Trends",
                CommandType.Text,
                null
                )
                );

            return res;
        }


        public bool Delete(int id)
        {
            bool res = false;
            int num =
                sqlHelper_.ExecuteCommand(
                "delete from Trends where Id=@Id",
                CommandType.Text,
                new SqlParameter[]
                {
                    new SqlParameter("@Id",id)
                }
                );
            if (num == 1)
                res = true;

            return res;
        }

        public QPS.NEW.Model.Trends GetModel(int Id)
        {
            QPS.NEW.Model.Trends trends = null;

            DataTable dt = sqlHelper_.GetDataTable(
                "select * from Trends where Id=@id",
                CommandType.Text,
                new System.Data.SqlClient.SqlParameter[]
                {
                    new System.Data.SqlClient.SqlParameter("@id",Id)
                }
                );

            if (dt != null && dt.Rows.Count > 0)
            {
                trends = new Model.Trends();

                trends.Id = Convert.ToInt32(dt.Rows[0]["Id"]);
                trends.Title = dt.Rows[0]["Title"].ToString();
                trends.Content = dt.Rows[0]["Content"].ToString();
                trends.Time = dt.Rows[0]["Time"].ToString();
               
            }

            return trends;
        }

        public bool Update(QPS.NEW.Model.Trends model)
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
            if (model.Title != null)
            {
                filedName[Count] = "Title";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Title);
                Count++;
            }
            if (model.Content != null)
            {
                filedName[Count] = "Content";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Content);
                Count++;
            }
            if (model.Time != null)
            {
                filedName[Count] = "time";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Time);
                Count++;
            }
           

            StringBuilder strSql = new StringBuilder();
            strSql.Append("update Trends set ");
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
    }
}
