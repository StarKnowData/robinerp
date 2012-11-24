using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;
using QPS.NEW.DAL;

namespace QPS.NEW.BLL
{
    public class Ad
    {
        private SQLHelper sqlHelper_;

        public Ad()
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
                " * from ad where id not in (select top ";
            strSql += (hasShowedPage * pageSize).ToString();
            strSql += " id from ad)";

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
                "select count(*) from ad",
                CommandType.Text,
                null
                )
                );

            return res;
        }

        public DataSet GetList(string strWhere)
        {
            DataSet da = null;
            da = sqlHelper_.GetDataSet(
                "select * from ad where "+strWhere,
                CommandType.Text,
                null
                );

            return da;
        }

        public bool Update(QPS.NEW.Model.ad model)
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
            if (model.Catid != null)
            {
                filedName[Count] = "catid";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Catid);
                Count++;
            }
            if (model.AdImg != null)
            {
                filedName[Count] = "adImg";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.AdImg);
                Count++;
            }
            if (model.AdUrl != null)
            {
                filedName[Count] = "adUrl";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.AdUrl);
                Count++;
            }
            if (model.AdType != null)
            {
                filedName[Count] = "adType";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.AdType);
                Count++;
            }
            if (model.AdName != null)
            {
                filedName[Count] = "adName";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.AdName);
                Count++;
            }
            if (model.AdDate != null)
            {
                filedName[Count] = "adDate";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.AdDate);
                Count++;
            }
           

            StringBuilder strSql = new StringBuilder();
            strSql.Append("update ad set ");
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
