using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using System.Data;
using Bzw.Data;

 
    public partial class Admin_FasciExchange_FasciExchangeEdit : AdminBasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            AdminPopedom.IsHoldModel("16");
            string id = CommonManager.Web.Request("id", "");
            string pname = CommonManager.Web.Request("pname", "");
            PrizeName.Value = pname;
            if (id != "")
            {
                DataTable dt = DbSession.Default.FromSql("select * from TCharmExchange where id=" + id).ToDataTable();
                if (dt.Rows.Count > 0)
                {
                    FasciNum.Value = dt.Rows[0]["CharmValue"].ToString();
                    PropCount.Value = dt.Rows[0]["PropCount"].ToString();
                }
            }
        }

        protected void PrCsEdit(object sender, EventArgs e)
        {
            string id = CommonManager.Web.Request("id", "");
            string  fasciNum, propCount;
             

            fasciNum = CommonManager.Web.Request("FasciNum", "0");

            if (!CommonManager.String.IsInteger(fasciNum) || Convert.ToInt32(fasciNum) <= 0)
            {
                CommonManager.Web.RegJs(this, "alert('魅力值数必须为大于0的整数！');location.href=location.href;", false);
            }

           propCount = CommonManager.Web.Request("PropCount", "0");

            if (!CommonManager.String.IsInteger(propCount) || Convert.ToInt32(propCount) <= 0)
            {
                CommonManager.Web.RegJs(this, "alert('道具数必须为大于0的整数！');location.href=location.href;", false);
            }
            DbSession.Default.FromSql("update TCharmExchange set CharmValue=" + fasciNum + ",PropCount=" + propCount + " where id=" + id).Execute();
            CommonManager.Web.RegJs(this, "alert('兑换设置修改成功！');location.href='FasciExchange.aspx';", false);
        }
    }
 
