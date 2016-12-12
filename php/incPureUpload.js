function checkFileUpload(form, extensions, requireUpload, sizeLimit, minWidth, minHeight, maxWidth, maxHeight, saveWidth, saveHeight) {
    var allUploadsOK = true;
    document.returnValue = false;
    for (var i = 0; i < form.elements.length; i++) {
        field = form.elements[i];
        if (field.type.toUpperCase() != 'FILE') {
            continue
        }
        checkOneFileUpload(field, extensions, requireUpload, sizeLimit, minWidth, minHeight, maxWidth, maxHeight, saveWidth, saveHeight);
        if (!field.uploadOK) {
            allUploadsOK = false;
            break
        }
    }
    if (allUploadsOK) {
        document.returnValue = true
    }
}

function checkOneFileUpload(field, extensions, requireUpload, sizeLimit, minWidth, minHeight, maxWidth, maxHeight, saveWidth, saveHeight) {
    var fileName = field.value.replace(/"/gi, '');
    field.uploadOK = false;
    if (fileName == '') {
        if (requireUpload) {
            alert('Você deve adicionar um título e imagem antes de enviar.');
            field.focus();
            return
        } else {
            field.uploadOK = true
        }
    } else {
        if (extensions != '') {
            checkFileExtension(field, fileName, extensions)
        } else {
            field.uploadOK = true
        } if (!document.layers && field.uploadOK) {
            document.PU_uploadForm = field.form;
            re = new RegExp("\.(gif|jpg|png|bmp|jpeg)$", "i");
            if (re.test(fileName) && (sizeLimit != '' || minWidth != '' || minHeight != '' || maxWidth != '' || maxHeight != '' || saveWidth != '' || saveHeight != '')) {
                checkImageDimensions(field, sizeLimit, minWidth, minHeight, maxWidth, maxHeight, saveWidth, saveHeight)
            }
        }
    }
    return
}

function checkFileExtension(field, fileName, extensions) {
    var re = new RegExp("\\.(" + extensions.replace(/,/gi, "|").replace(/\s/gi, "") + ")$", "i");
    var agt = navigator.userAgent.toLowerCase();
    var is_mac = (agt.indexOf("mac") != -1);
    var is_op = (agt.indexOf("opera") != -1);
    if (is_op) {
        var ext = fileName.substring(fileName.lastIndexOf('.') + 1, fileName.length);
        var extArr = extensions.split(',');
        var extCheck = false;
        for (var i = 0; i < extArr.length; i++) {
            if (extArr[i].toLowerCase() == ext.toLowerCase()) {
                extCheck = true;
                break
            }
        }
        if (extCheck == false) {
            alert('Este tipo de arquivo não é permitido.\nApenas os arquivos das seguintes extensões são permitidos: ' + extensions + '.\nPor favor, selecione outro arquivo e tente novamente.');
            field.focus();
            field.uploadOK = false;
            return
        }
    } else {
        if (!re.test(fileName)) {
            alert('Este tipo de arquivo não é permitido.\nApenas os arquivos das seguintes extensões são permitidos: ' + extensions + '.\nPor favor, selecione outro arquivo e tente novamente.');
            field.focus();
            field.uploadOK = false;
            return
        }
    }
    field.uploadOK = true
}

function checkImageDimensions(field, sizeL, minW, minH, maxW, maxH, saveW, saveH) {
    var agt = navigator.userAgent.toLowerCase();
    var is_mac = (agt.indexOf("mac") != -1);
    var is_ie = document.all;
    var is_ns6 = (!document.all && document.getElementById ? true : false);
    var fileURL = field.value;
    if (is_ie && is_mac) {
        begPos = fileURL.indexOf('/', 1);
        if (begPos != -1) {
            fileURL = fileURL.substring(begPos + 1, fileURL.length)
        }
    }
    fileURL = 'file:///' + fileURL.replace(/:\\/gi, '|/').replace(/\\/gi, '/').replace(/:([^|])/gi, '/$1').replace(/"/gi, '').replace(/^\//, '');
    if (!field.gp_img || (field.gp_img && field.gp_img.src != fileURL) || is_ns6) {
        if (is_ie && is_mac) {
            var dummyImage;
            dummyImage = document.createElement('IMG');
            dummyImage.src = 'dummy.gif';
            dummyImage.name = 'PPP';
            field.gp_img = dummyImage
        } else {
            field.gp_img = new Image()
        }
        with(field) {
            gp_img.field = field;
            gp_img.sizeLimit = sizeL * 1024;
            gp_img.minWidth = minW;
            gp_img.minHeight = minH;
            gp_img.maxWidth = maxW;
            gp_img.maxHeight = maxH;
            gp_img.saveWidth = saveW;
            gp_img.saveHeight = saveH;
            gp_img.onload = showImageDimensions;
            gp_img.src = fileURL + '?a=123'
        }
    }
}

function showImageDimensions(fieldImg) {
    var is_ns6 = (!document.all && document.getElementById ? true : false);
    var img = (fieldImg && !is_ns6 ? fieldImg : this);
    if (img.width > 0 && img.height > 0) {
        if ((img.minWidth != '' && img.minWidth > img.width) || (img.minHeight != '' && img.minHeight > img.height)) {
            alert('A imagem selecionada é muito pequena!\nO tamanho mínimo (altura/largura) é ' + img.minWidth + ' x ' + img.minHeight);
            img.field.uploadOK = false;
            return
        }
        if ((img.maxWidth != '' && img.width > img.maxWidth) || (img.maxHeight != '' && img.height > img.maxHeight)) {
            alert('A imagem selecionada é muito grande!\nO tamanho máximo (altura/largura) é ' + img.maxWidth + ' x ' + img.maxHeight);
            img.field.uploadOK = false;
            return
        }
        if (img.sizeLimit != '' && img.fileSize > img.sizeLimit) {
            alert('O tamanho do arquivo selecionado é muito grande!\nO tamanho de arquivo permitido é de ' + (img.sizeLimit / 1024) + ' KBytes');
            img.field.uploadOK = false;
            return
        }
        if (img.saveWidth != '') {
            document.PU_uploadForm[img.saveWidth].value = img.width
        }
        if (img.saveHeight != '') {
            document.PU_uploadForm[img.saveHeight].value = img.height
        }
        img.field.uploadOK = true
    }
}

function showProgressWindow(progressFile, popWidth, popHeight) {
    var showProgress = false,
        form, field;
    for (var f = 0; f < document.forms.length; f++) {
        form = document.forms[f];
        for (var i = 0; i < form.elements.length; i++) {
            field = form.elements[i];
            if (field.type.toUpperCase() != 'FILE') continue;
            if (field.value != '') {
                showProgress = true;
                break
            }
        }
    }
    if (showProgress && document.returnValue) {
        var w = 480,
            h = 340;
        if (document.all || document.layers || document.getElementById) {
            w = screen.availWidth;
            h = screen.availHeight
        }
        var leftPos = (w - popWidth) / 2,
            topPos = (h - popHeight) / 2;
        document.progressWindow = window.open(progressFile, 'ProgressWindow', 'toolbar=no,location=no,status=no,menubar=no,scrollbars=no,resizable=no,width=' + popWidth + ',height=' + popHeight);
        document.progressWindow.moveTo(leftPos, topPos);
        document.progressWindow.focus();
        window.onunload = function () {
            document.progressWindow.close()
        }
    }
}
