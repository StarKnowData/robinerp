function ChangeNewType(obj) {

    if (obj == 2) {
        document.getElementById("news2l").style.display = "block";
        document.getElementById("news1l").style.display = "none";
        document.getElementById("news2").src = "/Images/cont_btn02on.jpg";
        document.getElementById("news1").src = "/Images/cont_btn01off.jpg";
    }
    else {
        document.getElementById("news1l").style.display = "block";
        document.getElementById("news2l").style.display = "none";
        document.getElementById("news1").src = "/Images/cont_btn01on.jpg";
        document.getElementById("news2").src = "/Images/cont_btn02off.jpg";
    }
}
function ChangeOrd(obj) {
    for (var i = 1; i < 5; i++) {
        if (document.getElementById('sp' + i) != null) {
            if (i == 4) {
                document.getElementById('sp' + i).className = 'bg08';

            } else {
                document.getElementById('sp' + i).className = 'bg06';

            }
            document.getElementById('sp' + i + 'l').style.display = 'none';
        }

    }
    if (obj.id == "sp4") {
        obj.className = "bg07";
        document.getElementById(obj.id + 'l').style.display = 'block';
    } else {
        obj.className = "bg05";
        document.getElementById(obj.id + 'l').style.display = 'block';
    }

}
function ChangeMatch(num) {
    for (var i = 0; i < 5; i++) {
        if (document.getElementById("gr" + i) != null) {
            if (i == 4) {
                document.getElementById("gr" + i).className = "bg04";

            } else {
                document.getElementById("gr" + i).className = "bg02";

            }
        }
        document.getElementById("gl" + i + "l").style.display = "none";
    }
    if (document.getElementById("gr" + num) != null) {
        if (num == 4) {
            document.getElementById("gr" + num).className = "bg03";

        } else {
            document.getElementById("gr" + num).className = "bg01";

        }
    }
    document.getElementById("gl" + num + "l").style.display = "block";
}