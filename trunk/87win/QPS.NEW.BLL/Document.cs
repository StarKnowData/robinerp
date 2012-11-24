using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;
using QPS.NEW.DAL;

namespace QPS.NEW.BLL
{
    public class Document
    {
        private SQLHelper sqlHelper_;

        public Document()
        {
            sqlHelper_ = new SQLHelper(null);
        }

        public DataSet SelectList()
        {
            DataSet ds = null;

            ds = sqlHelper_.GetDataSet(
                "select * from Document",
                CommandType.Text,
                null
                );

            return ds;
        }

        public QPS.NEW.Model.Document GetModel(int Id)
        {
            QPS.NEW.Model.Document doc = null;

            DataTable dt = sqlHelper_.GetDataTable(
                "select * from Users where Id=@id",
                CommandType.Text,
                new System.Data.SqlClient.SqlParameter[]
                {
                    new System.Data.SqlClient.SqlParameter("@id",Id)
                }
                );

            if (dt != null && dt.Rows.Count > 0)
            {
                doc = new Model.Document();

                doc.Id = Convert.ToInt32(dt.Rows[0]["Id"]);
                doc.DTity = dt.Rows[0]["DTity"].ToString();
                doc.DContent = dt.Rows[0]["DContent"].ToString();
                doc.DType = dt.Rows[0]["DType"].ToString();
                doc.DTime = dt.Rows[0]["DTime"].ToString();

            }

            return doc;
        }

        public bool Update(QPS.NEW.Model.Document model)
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
            if (model.DTity != null)
            {
                filedName[Count] = "DTity";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.DTity);
                Count++;
            }
            if (model.DTime != null)
            {
                filedName[Count] = "DTime";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.DTime);
                Count++;
            }
            if (model.DContent != null)
            {
                filedName[Count] = "DContent";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.DContent);
                Count++;
            }
            if (model.DType != null)
            {
                filedName[Count] = "DType";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.DType);
                Count++;
            }
          

            StringBuilder strSql = new StringBuilder();
            strSql.Append("update Document set ");
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
