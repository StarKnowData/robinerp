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
                integral.Content =Convert.ToInt32( dt.Rows[0]["Content"]);
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

        public int Add(QPS.NEW.Model.Integral intergral)
        {

                string strSql = "";
                strSql += "insert into Integral(UserID,Content,CreateTime,RoomId,OrderId) ";
                strSql += "values(@UserID,@Content,@CreateTime,@RoomId,@OrderId)";

                int res = -1;
                res = sqlHelper_.ExecuteCommand(
                    strSql,
                    CommandType.Text,
                    new System.Data.SqlClient.SqlParameter[]
                {
                    new SqlParameter("@UserID",intergral.UserID),
                    new SqlParameter("@Content",intergral.Content),
                    new SqlParameter("@CreateTime",intergral.CreateTime),
                    new SqlParameter("@RoomId",intergral.RoomId),
                    new SqlParameter("@OrderId",intergral.OrderId),
                }
                    );

                if (res != 1)
                {
                    throw new Exception("Error:写入数据库失败");
                }

            return 1;
        }
    }
}
