using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using UiCommon;

namespace Bzw.Web.Public
{
	public partial class WebShortCutKey : System.Web.UI.UserControl
	{
		public int isDisplay = 1;	//公共属性，控制容器的显示,0为隐藏，其他值都为显示
        public string fullUrl = string.Empty;
        public string smallUrl = string.Empty;
		protected void Page_Load( object sender, EventArgs e )
		{
			 
            BLL.Game BllGame = new BLL.Game();
            fullUrl = BllGame.GetDownUrl("dianxindown");
            smallUrl = BllGame.GetDownUrl("wangtongdown");
            //if( !string.IsNullOrEmpty( UserLoginInfo.UserID ) )
            //{
            //     loginId.Visible = false;
            //}
		}
	}
}