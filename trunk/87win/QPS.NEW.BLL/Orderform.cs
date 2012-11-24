using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;
using QPS.NEW.DAL;

namespace QPS.NEW.BLL
{
    public class Orderform
    {
        private SQLHelper sqlHelper_;

        public Orderform()
        {
            sqlHelper_ = new SQLHelper(null);
        }

        public int Add(QPS.NEW.Model.Orderform model)
        {
            int res = 0;
            bool isOrdered = false;


            string strSql =
                "select count(*) from Orderform where Roomid=@roomid and IsDelete=0 and IsValidity=1";
            int num =Convert.ToInt32(
                sqlHelper_.GetSingle(
                strSql,
                CommandType.Text,
                new System.Data.SqlClient.SqlParameter[]
                {
                    new System.Data.SqlClient.SqlParameter("@roomid",model.Roomid)
                }
                )
                );

            if (num > 0)
            {
                isOrdered = true;
            }

            if (num < 0)
            {
                res = -1;
                throw new Exception("Error:查询数据库失败");
            }

            if (isOrdered)
            {
                res = -1;
                throw new Exception("Error:房间已被预定");
            }
            else
            {
                strSql =
                    "insert into Orderform(OrderNumber,StartTime,endTime,Userid,Roomid)";
                strSql += "values(@ordernumber,@starttime,@endtime,@userid,@roomid)";

                num = sqlHelper_.ExecuteCommand(
                    strSql,
                    CommandType.Text,
                    new System.Data.SqlClient.SqlParameter[]
                    {
                        new System.Data.SqlClient.SqlParameter("@ordernumber",model.OrderNumber),
                        new System.Data.SqlClient.SqlParameter("@starttime",model.StartTime),
                        new System.Data.SqlClient.SqlParameter("@endtime",model.endTime),
                        new System.Data.SqlClient.SqlParameter("@userid",model.Userid),
                        new System.Data.SqlClient.SqlParameter("@roomid",model.Roomid)
                    }
                    );
                if (num != 1)
                {
                    res = -1;
                    throw new Exception("Error:查询数据库失败");
                }
                else
                {
                    res = 1;
                }
            }


            return res;
        }

        public List<QPS.NEW.Model.Orderform> GetModelList(string strWhere)
        {
            List<QPS.NEW.Model.Orderform> list = new List<Model.Orderform>();
            QPS.NEW.Model.Orderform orderform = new Model.Orderform();

            DataTable dt = sqlHelper_.GetDataTable(
               "select * from Orderform where "+strWhere,
               CommandType.Text,
                null
               );

            if (dt != null)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    orderform.Id = Convert.ToInt32(dt.Rows[i]["Id"]);
                    orderform.OrderNumber = dt.Rows[i]["OrderNumber"].ToString();
                    orderform.StartTime = Convert.ToDateTime(dt.Rows[i]["StartTime"]);
                    orderform.endTime = Convert.ToDateTime(dt.Rows[i]["endTime"]);
                    orderform.Userid = Convert.ToInt32( dt.Rows[i]["Userid"]);
                    orderform.Roomid =  Convert.ToInt32( dt.Rows[i]["Roomid"]);
                    orderform.RoomType =  Convert.ToInt32(dt.Rows[i]["RoomType"]);
                    orderform.Beveragecost = Convert.ToDecimal( dt.Rows[i]["Beveragecost"] );
                    orderform.IsDelete = Convert.ToInt32(dt.Rows[i]["IsDelete"]);
                    orderform.IsValidity = Convert.ToInt32(dt.Rows[i]["IsValidity"]);

                    list.Add(orderform);
                }
            }

            return list;
        }

        public DataSet GetList(string strWhere)
        {
            DataSet ds = null;

            string strSql = "select * from Orderform where " + strWhere;

            ds = sqlHelper_.GetDataSet(strSql, CommandType.Text, null);

            return ds;
        }

        public bool Delete(int Id)
        {
            bool res=false;
            string strSql = "delete from Orderform where Id=@id";
            int num=-1;

            num=
                sqlHelper_.ExecuteCommand(
                strSql,
                CommandType.Text,
                new System.Data.SqlClient.SqlParameter[]
                {
                    new System.Data.SqlClient.SqlParameter("@id",Id)
                }
                );
            if (num == 1)
            {
                res = true;
            }

            return res;
        }

        public QPS.NEW.Model.Orderform GetModel(int Id)
        {
            QPS.NEW.Model.Orderform orderform = null;

            DataTable dt = sqlHelper_.GetDataTable(
                "select * from Orderform where Id=@id",
                CommandType.Text,
                new System.Data.SqlClient.SqlParameter[]
                {
                    new SqlParameter("@id",Id)
                }
                );

            if (dt != null && dt.Rows.Count > 0)
            {
                orderform = new Model.Orderform();

                orderform.Id = Convert.ToInt32(dt.Rows[0]["Id"]);
                orderform.OrderNumber = dt.Rows[0]["OrderNumber"].ToString();
                if (dt.Rows[0]["StartTime"] == DBNull.Value)
                    orderform.StartTime = null;
                else
                    orderform.StartTime = Convert.ToDateTime( dt.Rows[0]["StartTime"] );

                if (dt.Rows[0]["endTime"] == DBNull.Value)
                    orderform.endTime = null;
                else
                    orderform.endTime = Convert.ToDateTime(dt.Rows[0]["endTime"]);

                orderform.Userid = Convert.ToInt32(dt.Rows[0]["Userid"]);


                orderform.Roomid = Convert.ToInt32(dt.Rows[0]["Roomid"]);

                if (dt.Rows[0]["RoomType"] == DBNull.Value)
                    orderform.RoomType = null;
                else
                    orderform.RoomType = Convert.ToInt32(dt.Rows[0]["RoomType"]);

                if (dt.Rows[0]["Beveragecost"] == DBNull.Value)
                    orderform.Beveragecost = null;
                else
                    orderform.Beveragecost=Convert.ToDecimal(dt.Rows[0]["Beveragecost"]);

                orderform.IsDelete = Convert.ToInt32(dt.Rows[0]["IsDelete"]);

                if (dt.Rows[0]["IsValidity"] == DBNull.Value)
                    orderform.IsValidity = null;
                else
                    orderform.IsValidity = Convert.ToInt32(dt.Rows[0]["IsValidity"]);
            }

            return orderform;
        }


        public bool Update(QPS.NEW.Model.Orderform model)
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
            if (model.OrderNumber != null)
            {
                filedName[Count] = "OrderNumber";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.OrderNumber);
                Count++;
            }
            if (model.StartTime != null)
            {
                filedName[Count] = "StartTime";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.StartTime);
                Count++;
            }
            if (model.endTime != null)
            {
                filedName[Count] = "endTime";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.endTime);
                Count++;
            }
            if (model.Userid != -999)
            {
                filedName[Count] = "Userid";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Userid);
                Count++;
            }
            if (model.Roomid != -999)
            {
                filedName[Count] = "Roomid";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Roomid);
                Count++;
            }
            if (model.RoomType != null)
            {
                filedName[Count] = "RoomType";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.RoomType);
                Count++;
            }
            if (model.Beveragecost != null)
            {
                filedName[Count] = "Beveragecost";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.Beveragecost);
                Count++;
            }
            if (model.IsDelete != -999)
            {
                filedName[Count] = "IsDelete";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.IsDelete);
                Count++;
            }
            if (model.IsValidity != null)
            {
                filedName[Count] = "IsValidity";
                paramName[Count] = "@" + filedName[Count];
                sqlParams[Count] = new SqlParameter(paramName[Count], model.IsValidity);
                Count++;
            }

            StringBuilder strSql = new StringBuilder();
            strSql.Append("update Orderform set ");
            for (int i = 1; i < Count; i++)    // i begin with 0 !!!
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

        public bool UpdateType(string Id, string RoomType)
        {
            bool res=false;
            string strSql = "update Orderform set RoomType=@RoomType where Id=@Id";
            int num =
                sqlHelper_.ExecuteCommand(
                strSql,
                CommandType.Text,
                new SqlParameter[]
                {
                    new SqlParameter("@RoomType",RoomType),
                    new SqlParameter("@Id",Id)
                }
                );
            if (num == 1)
            {
                res = true;
            }

            return res;
        }


        public DataSet SelectRoom(int pageSize, int currentPage)
        {
            int hasShowedPage=0;

            hasShowedPage=currentPage-1>=0?currentPage-1:0;

            string strSql="select top ";
            strSql+=pageSize.ToString();
            strSql +=
                " * from Orderform where Id not in (select top ";
            strSql+=(hasShowedPage*pageSize).ToString();
            strSql+=" Id from Orderform)";
            
            DataSet ds=null;
            ds = sqlHelper_.GetDataSet(
                strSql,
                CommandType.Text,
                null
                );

            return ds;
        }

        public DataSet SelectList(string strWhere)
        {
            DataSet ds = null;
            ds = sqlHelper_.GetDataSet(
                "select * from Orderform where "+strWhere,
                CommandType.Text,
                null
                );

            return ds;
        }

        public int GetCount()
        {
            int res = -999;

            res =Convert.ToInt32( 
                sqlHelper_.GetSingle(
                "select count(*) from Orderform",
                CommandType.Text,
                null
                )
                );

            return res;
        }

        public bool UpdateIsDelete(string Id, string ifDelete)
        {
            bool res = false;
            string strSql = "update Orderform set IsDelete=@isDelete where Id=@Id";
            int num =
                sqlHelper_.ExecuteCommand(
                strSql,
                CommandType.Text,
                new SqlParameter[]
                {
                    new SqlParameter("@isDelete",ifDelete),
                    new SqlParameter("@Id",Id)
                }
                );
            if (num == 1)
            {
                res = true;
            }

            return res;
        }
    }
}
