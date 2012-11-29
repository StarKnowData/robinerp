using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;

namespace Bzw.Web.Public
{
	public partial class WebTop : System.Web.UI.UserControl
	{
		public int pageType = 0;
        public string strUrl;
        public string strSrc;
		protected void Page_Load( object sender, EventArgs e )
		{
            DataTable dt;
             if (Session["gamelist"] == null)
             {
        dt = new BLL.Game().List(0);
               Session["gamelist"] = dt;
              
                
             }
             else
             {
                 dt = (DataTable)Session["gamelist"];

             }
            if (dt.Rows.Count > 0)
            {
                foreach (DataRow row in dt.Rows)
                {
                    strUrl =strUrl+ "/GameInfo.aspx?id=" + row["Game_id"].ToString() + ",";
                    strSrc =strSrc+ row["Image_URL"].ToString() + ",";
                }
            }
		}
	}
}