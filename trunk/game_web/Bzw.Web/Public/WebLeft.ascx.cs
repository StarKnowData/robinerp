using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BLL;

namespace Bzw.Web.Public
{
    public partial class WebLeft : System.Web.UI.UserControl
    {
        public int helpid = 0;
        public int serviceid = 0;
        protected void Page_Load(object sender, EventArgs e)
        {
            News news = new News();
            this.rptNewUsers.DataSource = news.ListByTypeName("新手指南", 6);
            this.rptNewUsers.DataBind();
            //this.rptSer.DataSource = news.ListByTypeName("客服中心", 6);
            //this.rptSer.DataBind();
        }
    }
}