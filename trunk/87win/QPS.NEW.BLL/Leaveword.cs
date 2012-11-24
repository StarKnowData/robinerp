using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
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
    }
}
