using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;
using BCST.Common;
using System.Configuration;

 
    public partial class Admin_FasciExchange_FasciPropAdd :AdminBasePage{

        protected void Page_Load(object sender, EventArgs e)
        {
            AdminPopedom.IsHoldModel("16");
            if (!IsPostBack)
            {
                DataTable dt = DbSession.Default.FromSql("select * from TPropDefine where propid not in (select propid from TCharmExchange)").ToDataTable();
                ddlPropType.Items.Clear();
                if (Convert.ToInt32(DbSession.Default.FromSql("select count(0) from TCharmExchange where propid=0").ToScalar()) == 0)
                {
                    ddlPropType.Items.Add(new ListItem(ConfigurationManager.AppSettings["moneyName"], "0"));
                }
                if (dt.Rows.Count > 0)
                {
                    foreach (DataRow row in dt.Rows)
                    {
                        ddlPropType.Items.Add(new ListItem(row["PropName"].ToString(), row["PropID"].ToString()));
                    }
                }
              
            }
        }

        protected void PrCsEdit(object sender, EventArgs e)
        {
             string PropID, FasciNum, PropCount;
             PropID = ddlPropType.SelectedValue;
           
            FasciNum = CommonManager.Web.Request("FasciNum", "0");

            if (!CommonManager.String.IsInteger(FasciNum) || Convert.ToInt32(FasciNum)<=0)
            {
                CommonManager.Web.RegJs(this, "alert('魅力值数必须为大于0的整数！');location.href=location.href;", false);
            }

            PropCount = CommonManager.Web.Request("PropCount", "0");

            if (!CommonManager.String.IsInteger(PropCount) || Convert.ToInt32(PropCount) <= 0)
            {
                CommonManager.Web.RegJs(this, "alert('道具数必须为大于0的整数！');location.href=location.href;", false);
            }
            
            //插入奖品数据到道具表中,并且添加魅力兑换设置
            int sqlStatus = DbSession.Default.FromSql("insert into TCharmExchange( CharmValue, PropID, PropCount) values("+FasciNum+","+PropID+","+PropCount+") ")  .Execute();
       if (sqlStatus > 0)
           CommonManager.Web.RegJs(this, "alert('设置成功！');location.href='FasciExchange.aspx';", false);
       else
           CommonManager.Web.RegJs(this, "alert('设置失败！');history.go(-1);", false);
        }
        }
    
 
