using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using QPS.NEW.DAL;

namespace QPS.NEW.BLL
{
    public class Orderform
    {
        private QPS.NEW.Model.Orderform orderform_;
        private SQLHelper sqlHelper_;

        public Orderform()
        {
            sqlHelper_ = new SQLHelper(null);
        }

        public int Add(QPS.NEW.Model.Orderform model)
        {
            int res = 0;
            bool isOrdered = false;

            orderform_=model;

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
    }
}
