using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;

using System.Web.UI.WebControls;
using System.Configuration;
using IpHandle;
using BCST.Common;
using System.Data;
using Bzw.Data;

 
    public partial class Admin_Users_UserLoginSearch :AdminBasePage
    {
        public int Userids = 0;
        protected void Page_Load(object sender, EventArgs e)
        {
            AdminPopedom.IsHoldModel("04");
            if (!IsPostBack)
            {
                UsersLoginList();
            }
        }

        public void UsersLoginList()
        {
            string bt = CommonManager.Web.Request("bt", "");
            string et = CommonManager.Web.Request("et", "");
            string kw = CommonManager.Web.Request("kw", "").Replace('$','\\');
            string isLike = CommonManager.Web.Request("IsLike", "");
            string selType = CommonManager.Web.Request("sel", "");//关键字类别
            string sel2 = CommonManager.Web.Request("sel2", "");//某条件如：ip/matchinecode
            string sel3 = CommonManager.Web.Request("sel3", "");//玩家状态
            string sel4 = CommonManager.Web.Request("sel4", "");//排列条件
            string sel5 = CommonManager.Web.Request("sel5", "desc");//排列方式
            string loginCount = CommonManager.Web.Request("loginCount", "0");//某条件下登录的次数
            string sqlWhere = "";
            string order = "";
         
            if (sel4 == "mcode")
            {
                order = " MachineCode " + sel5;
            }
            else if (sel4 == "ip")
            {
                order = "LastLoginIP "+sel5;
            }
            else
            { 
            order= "LastLoginTM "+sel5;
            }
          
           
           
            if (bt != "")
            {
                sqlWhere += " and LastLoginTm>='"+bt+"'";
            }
            if (et != "")
            {
                sqlWhere += " and LastLoginTM<='"+et+"'";
            }
            if (kw != "")
            {
              
                if (selType == "1")
                {
                    sqlWhere +=(isLike=="1")? " and username  like '%"+kw+"%'":" and username='"+kw+"'";
                    
                }
                else if (selType == "2")
                {
                    sqlWhere += (isLike == "1") ? " and userid like '%"+kw+"%'" : " and userid="+kw ;
                }
                else if (selType == "3")
                {
                    sqlWhere += (isLike == "1") ? " and LastLoginIP like '%" + kw + "%'" : " and LastLoginIP='" + kw + "'";
                }
                else if( selType=="4")
                {
                      sqlWhere += (isLike == "1") ? " and machinecode like '%" + kw + "%'" : " and machinecode='" + kw + "'";
                }
                else 
                {
                    
                    sqlWhere += (isLike == "1") ? " and HardID like '%"+kw+"%'" : " and HardID='"+kw+"'";
                  
                }
            }
            if (sel3 != "" && sel3 != "0")  
            {
                if (sel3 == "1")
                {
                    sqlWhere += " and [disabled]=1 or machinecode in (select LockCode from TLockCode) or lastloginip in (select accessipchar from TGameIPRule where LimitedLogon<>0)  ";
                }
                else
                {
                    sqlWhere += " and [disabled]=0 and machinecode not in (select LockCode from TLockCode) and lastloginip not in (select accessipchar from TGameIPRule where LimitedLogon<>0)";
                }
 
            }
            if (loginCount != "0")
            {
                if (sel2 == "ip")
                    sqlWhere += " and lastloginip IN ( SELECT lastloginip FROM web_vuserloginlist GROUP BY lastloginip HAVING COUNT(lastloginip)>" + loginCount+")";
                else
                    sqlWhere += " and MachineCode in (select MachineCode from Web_vuserLoginList GROUP BY MachineCode  having  count(machinecode)>" + loginCount+")";

                
            }
     
         
            DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
       .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
       .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
       .AddInputParameter("@Columns", DbType.String, "*")
       .AddInputParameter("@TableName", DbType.String, "Web_vUserLoginList")
       .AddInputParameter("@Wheres", DbType.String, sqlWhere)
       .AddInputParameter("@KeyName", DbType.String, "UserID")
       .AddInputParameter("@OrderBy", DbType.String, order)
       .ToDataSet();
           
            if (ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0)
            {

                
                anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
                anpPageIndex.CurrentPageIndex = PageIndex;
                DataTable dt = ds.Tables[1];
                dt.Columns.Add("IsLimitIP", typeof(bool));
                dt.Columns.Add("IsLockCode", typeof(bool));
                dt.Columns.Add("IsLockHard",typeof(bool));
                foreach (DataRow row in dt.Rows)
                {
                    
                    row["IsLimitIP"] = DbSession.Default.FromSql("select count(AccessIPChar) from TGameIPRule where LimitedLogon<>0 and AccessIPChar='"+row["LastLoginIP"].ToString()+"'").ToScalar();
                    row["IsLockCode"] = DbSession.Default.FromSql("select count(LockCode) from TLockCode where LockCode='" + row["MachineCode"].ToString() + "'").ToScalar();
                    row["IsLockHard"] = DbSession.Default.FromSql("select count(LockHard) from TLockCode where LockHard='" + row["HardID"].ToString() + "'").ToScalar();
                 
                  
                }
                UserList.DataSource = dt;
                UserList.DataBind();
                UserList.Visible = true;
                NoUserList.Visible = false;
            }
            else
            {
                anpPageIndex.CurrentPageIndex = 1;
              
                this.NoUserList.Visible = true;
                UserList.Visible = false;
            }
        }

        public string GetAddressByIP(string ip)
        {
            string ipfilePath = ConfigurationManager.AppSettings["IPDataUrl"];
            IPSearch ipSearch = new IPSearch(ipfilePath);
            IPSearch.IPLocation loc = ipSearch.GetIPLocation(ip);
            return loc.country;
        }
    }
 

