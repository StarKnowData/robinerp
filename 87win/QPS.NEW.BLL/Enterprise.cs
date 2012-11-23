using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using QPS.NEW.DAL;

namespace QPS.NEW.BLL
{
    public class Enterprise
    {
        private QPS.NEW.Model.Enterprise enterprise_;

        public int Add(QPS.NEW.Model.Enterprise model)
        {

            int checkUsername = -1;

            enterprise_ = model;
            SQLHelper sqlHelper = new SQLHelper(null);
            checkUsername = Convert.ToInt32(
                sqlHelper.GetSingle("select count(*) from Enterprise where Username=@username",
                CommandType.Text,
                new System.Data.SqlClient.SqlParameter[]{
                    new System.Data.SqlClient.SqlParameter("@username",enterprise_.Username)
                }
                )
                );
            if (checkUsername != 0)
            {
                throw new Exception("Error:002-用户名已经存在");
            }
            else
            {

                string strSql = "";
                strSql += "insert into Enterprise(Username,Password,Nickname,Phone,Address,Mail,IfChecked) ";
                strSql += "values(@username,@password,@nickname,@phone,@address,@mail,@ifchecked)";

                int res = -1;
                res = sqlHelper.ExecuteCommand(
                    strSql,
                    CommandType.Text,
                    new System.Data.SqlClient.SqlParameter[]
                {
                    new System.Data.SqlClient.SqlParameter("@username",enterprise_.Username),
                    new System.Data.SqlClient.SqlParameter("@password",enterprise_.Password),
                    new System.Data.SqlClient.SqlParameter("@nickname",enterprise_.Nickname),
                    new System.Data.SqlClient.SqlParameter("@phone",enterprise_.Phone),
                    new System.Data.SqlClient.SqlParameter("@address",enterprise_.Address),
                    new System.Data.SqlClient.SqlParameter("@mail",enterprise_.Mail),
                    new System.Data.SqlClient.SqlParameter("@ifchecked",enterprise_.IfChecked)
                }
                    );

                if (res != 1)
                {
                    throw new Exception("Error:001-查询数据库失败");
                }
            }
            return 1;
        }

        public DataSet GetList(string strWhere)
        {
            DataSet ds = null;
            SQLHelper sqlHelper = new SQLHelper(null);
            string strSql = 
                "select * from Enterprise where " + strWhere;

            ds=sqlHelper.GetDataSet(strSql, CommandType.Text, null);

            return ds;
        }
    }
}
