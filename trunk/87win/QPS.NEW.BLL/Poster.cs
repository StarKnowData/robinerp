using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Data.SqlClient;
using QPS.NEW.DAL;

namespace QPS.NEW.BLL
{
    public class Poster
    {
        private SQLHelper sqlHelper_;

        public Poster()
        {
            sqlHelper_ = new SQLHelper(null);
        }

        public DataSet Select(int pageSize, int currentPage)
        {
            int hasShowedPage = 0;

            hasShowedPage = currentPage - 1 >= 0 ? currentPage - 1 : 0;

            string strSql = "select top ";
            strSql += pageSize.ToString();
            strSql +=
                " * from Poster where ID not in (select top ";
            strSql += (hasShowedPage * pageSize).ToString();
            strSql += " ID from Poster)";

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
                "select count(*) from Poster",
                CommandType.Text,
                null
                )
                );

            return res;
        }

        public DataSet GetList(string strWhere)
        {
            DataSet ds = null;

            ds = sqlHelper_.GetDataSet(
                "select * from Poster where "+strWhere,
                CommandType.Text,
                null
                );

            return ds;
        }

        public bool Update(QPS.NEW.Model.Poster model)
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
                filedName[Count] = "ID";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Id);
                Count++;
            }
            if (model.PhotoUrl != null)
            {
                filedName[Count] = "PhotoUrl";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.PhotoUrl);
                Count++;
            }
            if (model.URL != null)
            {
                filedName[Count] = "URL";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.URL);
                Count++;
            }
            

            StringBuilder strSql = new StringBuilder();
            strSql.Append("update Poster set ");
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

        public bool Delete(int id)
        {
            bool res = false;
            int num =
                sqlHelper_.ExecuteCommand(
                "delete from Poster where ID=@Id",
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
    }
}
