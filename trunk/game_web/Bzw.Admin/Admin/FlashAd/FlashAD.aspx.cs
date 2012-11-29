using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using Bzw.Data;
using System.IO;
public partial class Admin_FlashAd_FlashAD : AdminBasePage
{
    public int TableID;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("01");

		string xmlPath = Server.MapPath("/Upload/xml/flash.xml");
        if (!File.Exists(xmlPath))
        {
            return;
        }

        DataSet ds=new DataSet(); 
         ds.ReadXml(xmlPath);
         if (ds.Tables.Count > 0)
         {
             DataTable sd = ds.Tables[0];
             if (sd.Rows.Count > 0)
             {
                 FlashAdlist.DataSource = sd;
                 FlashAdlist.DataBind();
             }
             sd.Clear();
         }
         else
             return;

    }
}
