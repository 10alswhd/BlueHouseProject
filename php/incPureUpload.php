<?php
class pureFileUpload
{
	// Set version
	var $version = '2.1.2';
	var $debugger = false;
	// Define variables
	var $path;
	var $extensions;
	var $redirectURL;
	var $storeType;
	var $sizeLimit;
	var $nameConflict;
	var $minWidth;
	var $minHeight;
	var $maxWidth;
	var $maxHeight;
	var $saveWidth;
	var $saveHeight;
	var $timeout;
	
	var $fullpath;
	var $uploadedFile;
	var $uploadedFiles;
	var $addOns;
	
	function pureFileUpload() {
		global $DMX_debug;
		$this->uploadedFile = new fileInfo($this);
		$this->uploadedFiles = array();
		$this->addOns = array();
		$this->debugger = $DMX_debug;
		$this->debug("<br/><font color=\"#009900\"><b>Upload PHP ".$this->version."</b></font><br/><br/>");
	}
	
	// Check if version is uptodate
	function checkVersion($version) {
		if ($version < $this->version) {
			$this->error('version');
		}
	}
	
	// Cleanup illegal characters
	function cleanUpFileName(&$file) {
		$this->debug("<b>Limpando nome do arquivo...</b><br/>");
		$fileName = $file->getFileName();
		$fileName = substr($fileName, strrpos($fileName, ':'));
		$fileName = preg_replace("/\s+|;|\+|=|\[|\]|'|,|\\|\"|\*|<|>|\/|\?|\:|\|/i", "_", $fileName);
		$this->debug("new filename = <font color=\"#000099\"><b>".$fileName."</b></font><br/>");
		$file->setFileName($fileName);
	}
	
	// Check the dimensions of the image
	function checkImageDimension(&$file) {
		global $_POST;
		
		$this->debug("<b>Checando dimensão do arquivo...</b><br/>");
		// Get the imageSize
		if ($imageSize = GetImageSize($this->path.'/'.$file->fileName)) {
			$this->debug("imageWidth = <font color=\"#000099\"><b>".$imageSize[0]."</b></font><br/>");
			$this->debug("imageHeight = <font color=\"#000099\"><b>".$imageSize[1]."</b></font><br/>");
			// Check if it isn't to small
			if (($this->minWidth <> '' && $imageSize[0] < $this->minWidth) || ($this->minHeight <> '' && $imageSize[1] < $this->minHeight)) {
				$this->error('smallSize', $file->fileName);
			}
			// Check if it isn't to big
			if (($this->maxWidth <> '' && $imageSize[0] > $this->maxWidth) || ($this->maxHeight <> '' && $imageSize[1] > $this->maxHeight)) {
				$this->error('bigSize', $file->fileName);
			}
			// Set the post vars with the imageSize
			$this->debug("Configurando imagem...<br/>");
			$file->setImageSize($imageSize[0], $imageSize[1]);
			$_POST[$this->saveWidth] = $imageSize[0];
			$_POST[$this->saveHeight] = $imageSize[1];
		}
	}
	
	// Check if directory exist and create if needed
	function checkDir($dir) {
		$this->debug("<b>Checando diretório...</b><br/>");
		if (!is_dir($dir)) {
			$this->debug("diretório não existe<br/>");
			// Break directory apart
			$dirs = explode('/', $dir);
			$tempDir = $dirs[0];
			$check = false;
			
			for ($i = 1; $i < count($dirs); $i++) {
				$this->debug("Checking ".$tempDir."<br/>");
				if (is_writeable($tempDir)) {
					$check = true;
				} else {
					$error = $tempDir;
				}
				
				$tempDir .= '/'.$dirs[$i];
				// Check if directory exist
				if (!is_dir($tempDir)) {
					if ($check) {
						// Create directory
						$this->debug("Creating ".$tempDir."<br/>");
						mkdir($tempDir, 0777);
						chmod($tempDir, 0777);
					} else {
						// Sem permissões
						$this->error('permission', $error);
					}
				}
			}
		}
	}
	
	// Check the fileSize
	function checkFileSize(&$file) {
		$this->debug("<b>Checando tamanho...</b><br/>");
		if ($this->sizeLimit < $file->fileSize) {
			$this->error('size', $file->fileName);
		}
	}
	
	// Check if the extension is allowed
	function checkExtension(&$file) {
		$this->debug("<b>Checando extensão...</b><br/>");
		$allow = false;
		// Loop thrue the extensions
		foreach (preg_split('/,/', $this->extensions) as $extension) {
			
			// Check if it is allowed
			$this->debug("comparing <font color=\"#000099\"><b>".strtoupper($file->extension)."</b></font> with <font color=\"#000099\"><b>".strtoupper($extension)."</b></font><br/>");
			if (strtoupper($file->extension) == strtoupper($extension)) {
				$allow = true;
			}
		}
		
		// Give error when not allowed
		if (!$allow && $file->fileName <> '') {
			$this->error('extension', $file->fileName);
		}
	}
	
	// Create an unique name if file exists
	function createUniqName($fileName) {
		$this->debug("<b>Criando um nome único...</b><br/>");
		$uniq = 0;
		$name = substr($fileName, 0, strrpos($fileName, '.'));
		$extension = substr($fileName, strrpos($fileName, '.')+1);
		
		while (++$uniq) {
			// Check if file does not exist
			$this->debug("Checando <font color=\"#000099\"><b>".$name.'_'.$uniq.'.'.$extension."</b></font><br/>");
			if (!file_exists($this->path.'/'.$name.'_'.$uniq.'.'.$extension)) {
				// Return an uniq filename
				return ($name.'_'.$uniq.'.'.$extension);
			}
		}
	}
	
	// Move the file to the given location
	function moveFile($source, $destination) {
		$this->debug("<b>Movendo o arquivo...</b><br/>");
		// Check if you have write permissions
		$this->debug("Checando permissões...<br/>");
		if (is_writeable($this->path)) {
			if (move_uploaded_file($source, $destination)) {
				// Change file permissions
				chmod($destination, 0644);
				// Add filename to array with done files
				$this->done[] = $destination;
				$this->debug("arquivo movido para <font color=\"#000099\"><b>".$destination."</b></font><br/>");
			} else {
				// Give an error if no write permissions
				$this->error('writePerm', $destination);
			}
		} else {
			// Give an error if no write permissions
			$this->error('writePerm', $destination);
		}
	}
	
	function error($error, $extra) {
		switch ($error) {
		// Incorrect version
		case 'version':
	    echo "<b>Você não tem a última versão do incPHPupload.php no seru servidor.</b><br/>";
  	  echo "É necessário.<br/>";
			break;
		// Sem permissões to create folder
		case 'permission':
			echo "<b>Sem permissões</b><br/><br/>";
			echo "A pasta <b>".$extra."</b> não foi criada<br/>";
			echo "Set the permissions of the parentmap correctly<br/>";
			break;
		// Sem permissões to write an file
		case 'writePerm':
			echo "<b>Sem permissões</b><br/><br/>";
			echo "File <b>".$extra."</b> can not be created,<br/>";
			echo "Set the permissions of the parentmap correctly<br/>";
			break;
		// The imagesize is to small
		case 'smallSize':
			echo "<b>Erro no upload!</b><br/><br/>";
			echo "A imagem ".$extra." é muito pequena.<br/>";
			echo "O tamanho mínimo é de ".$this->minWidth." x ".$this->minHeight."<br/>";
			break;
		// The imagesize is to big
		case 'bigSize':
			echo "<b>Erro no upload!</b><br/><br/>";
			echo "A imagem ".$extra." é muito grande.<br/>";
			echo "O tamanho máximo é de ".$this->maxWidth." x ".$this->maxHeight."<br/>";
			break;
		// Filesize is to big
		case 'size':
			echo "<b>Tamanho do arquivo não permitido</b><br/><br/>";
			echo "Arquivo: ".$extra."<br/>";
			echo "O tamanho limite é de ".$this->sizeLimit." kb<br/>";
			break;
		// Extension is not allowed
		case 'extension':
			echo "<b>Extensão não permitida!</b><br/><br/>";
			echo "Arquivo: ".$extra."<br/>";
			echo "Apenas as seguintes extensões são permitidas: ".$this->extensions."<br/>";
			echo "Por favor, escolha outro arquivo e tente novamente.<br/>";
			break;
		// There was an error with the uploaded file
		case 'empty':		
			echo "<b>Erro no upload!</b><br/><br/>";
			echo "Arquivo: ".$extra."<br/>";
			echo "O arquivo não foi processado corretamente.<br/>";
			break;
		// File exists
		case 'exist':
			echo "<b>O arquivo já existe!</b><br/><br/>";
			echo "Arquivo: ".$extra."<br/>";
			break;
		}
		
		// Allow to go back and stop the script
		echo "Por favor corrija e <a href=\"javascript:history.back(1)\">tenta novamente</a>.";
		
		$this->failUpload();
		// Stop the script
		exit;
	}
	
	function doUpload() {
		global $_POST,$_SERVER,$_FILES;
		// Debugger info
		$this->debug("PHP version(<font color=\"#990000\">".phpversion()."</font>)<br/>");
		$this->debug("path(<font color=\"#990000\">".$this->path."</font>)<br/>");
		$this->debug("extensions(<font color=\"#990000\">".$this->extensions."</font>)<br/>");
		$this->debug("redirectURL(<font color=\"#990000\">".$this->redirectURL."</font>)<br/>");
		$this->debug("storeType(<font color=\"#990000\">".$this->storeType."</font>)<br/>");
		$this->debug("sizeLimit(<font color=\"#990000\">".$this->sizeLimit."</font>)<br/>");
		$this->debug("nameConflict(<font color=\"#990000\">".$this->nameConflict."</font>)<br/>");
		$this->debug("minWidth(<font color=\"#990000\">".$this->minWidth."</font>)<br/>");
		$this->debug("minHeight(<font color=\"#990000\">".$this->minHeight."</font>)<br/>");
		$this->debug("maxWidth(<font color=\"#990000\">".$this->maxWidth."</font>)<br/>");
		$this->debug("maxHeight(<font color=\"#990000\">".$this->maxHeight."</font>)<br/>");
		$this->debug("saveWidth(<font color=\"#990000\">".$this->saveWidth."</font>)<br/>");
		$this->debug("saveHeight(<font color=\"#990000\">".$this->saveHeight."</font>)<br/>");
		$this->debug("timeout(<font color=\"#990000\">".$this->timeout."</font>)<br/>");
		// Set the timeout
		$this->debug("Configurando...<br/>");
		@set_time_limit($this->timeout);
		
		// Get the fullpath
		$this->fullPath = '/'.substr($_SERVER['PHP_SELF'], 1, strrpos($_SERVER['PHP_SELF'], '/')).$this->path.'/';
		$this->debug("fullPath = <font color=\"#000099\"><b>".$this->fullPath."</b></font><br/>");
		
		// Check if directory exists and create if needed
		$this->checkDir($this->path);
		
		// Go through all the files
		$this->debug("<b>Carregando...</b><br/>");
		foreach ($_FILES as $field => $value) {
			$file = new fileInfo($this);
			$file->field = $field;
			$file->setfileName($_FILES[$field]['name'],$_FILES[$field]['size']);
			$this->debug("field = <font color=\"#000099\"><b>".$file->field."</b></font><br/>");
			$this->debug("filename = <font color=\"#000099\"><b>".$file->fileName."</b></font><br/>");
			
			// Clean file from illegal characters
			$this->cleanUpFileName($file);
			// Check filesize if limit is given
			if ($this->sizeLimit <> '') {
				$this->checkFileSize($file);
			}
			
			// Check the filename extension
			if ($this->extensions <> '') {
				$this->checkExtension($file);
			}
			
			// Check if file is uploaded correctly
			if (is_uploaded_file($_FILES[$field]['tmp_name'])) {
				// Check if filename exists
				if (file_exists($this->path.'/'.$file->fileName)) {
					// What to do if filename exists
					switch ($this->nameConflict) {
					// Overwrite the file
					case 'over':
						$this->debug("Overwrite existing file<br/>");
						$this->moveFile($_FILES[$field]['tmp_name'], $this->path.'/'.$file->fileName);
						break;
					// Give error message
					case 'error':
						$this->debug("Error<br/>");
						$this->error('exist', $file->fileName);
						break;
					// Make an unique name
					case 'uniq':
						$file->setFileName($this->createUniqName($file->fileName));
						$this->moveFile($_FILES[$field]['tmp_name'], $this->path.'/'.$file->fileName);
						break;
					}
				} else {
					// If filename does not exist
					$this->moveFile($_FILES[$field]['tmp_name'], $this->path.'/'.$file->fileName);
				}
				
				// Check the imagesize
				$this->checkImageDimension($file);
				
				// Put fileinfo in array
				$this->uploadedFiles[$field] = $file;
				
			} elseif ($file->fileName <> '') {
				// The file is 0 in size or is not uploaded correctly
				$this->error('empty', $file->fileName);
			} else {
				// No file is uploaded
				$_POST[$field] = '';
			}
		}
		
		// Recreate the redirectURL
		if ($this->redirectURL <> '') {
			if (isset($_SERVER['QUERY_STRING'])) {
				$this->redirectURL .= (strpos($this->redirectURL, '?')) ? '&' : '?';
				$this->redirectURL .= $_SERVER['QUERY_STRING'];
			}
			header(sprintf("Location: %s", $this->redirectURL));
		}
	}
	
	// Debugger
	function debug($info) {
		if ($this->debugger) {
			echo "<font face=\"verdana\" size=\"2\">".$info."</font>";
		}
	}
	// Register addons and put them in an array
	function registerAddOn(&$addOn) {
		array_push($this->addOns, $addOn);
	}
	
	function failUpload() {
		foreach ($this->addOns as $addOn) {
			$addOn->cleanUp();
		}
		// Check if some files are already uploaded
		if (isset($this->uploadedFiles)) {
			if (count($this->uploadedFiles) > 0) {
				foreach ($this->uploadedFiles as $file) {
					// Delete the file
					unlink($this->path.'/'.$file->fileName);
				}
			}
		}
	}
}
class pureUploadAddon
{
	var $upload;
	
	function pureUploadAddon(&$upload) {
		$this->upload = &$upload;
	}
	
	function cleanUp() {
	}
}
class fileInfo
{
	var $field;
	var $fileName;
	var $fileSize;
	var $filePath;
	var $thumbFileName;
	var $thumbName;
	var $thumbExtension;
	var $thumbSize;
	var $thumbPath;
	var $thumbNaming;
	var $thumbSuffix;
	var $name;
	var $extension;
	var $imageWidth;
	var $imageHeight;
	var $thumbWidth;
	var $thumbHeight;
	
	var $upload;
	
	function fileInfo(&$upload) {
		$this->upload = &$upload;
	}
	
	function setFileName($newFileName, $fileSize = "") {
		global $_POST;
		$this->fileName = $newFileName;
		$this->filePath = $this->upload->path;
		$this->name = substr($newFileName, 0, strrpos($newFileName, '.'));
		$this->extension = substr($newFileName, strrpos($newFileName, '.')+1);
		if ($fileSize == "") {
			if (file_exists($this->upload->path."/".$this->fileName)) {
				$this->fileSize = round((filesize($this->upload->path."/".$this->fileName)/1024), 0);
			}
		} else {
			$this->fileSize = round(($fileSize/1024), 0);
		}
		if ($this->upload->storeType == 'path') {
			$_POST[$this->field] = $this->upload->fullPath.$this->fileName;
		} else {
			$_POST[$this->field] = $this->fileName;
		}
		$this->upload->uploadedFiles[$this->field] = $this;
	}
	function setThumbFileName($newFileName, $path, $naming, $suffix) {
		$this->thumbFileName = $newFileName;
		$this->thumbPath = $path;
		$this->thumbNaming = $naming;
		$this->thumbSuffix = $suffix;
		$this->thumbName = substr($newFileName, 0, strrpos($newFileName, '.'));
		$this->thumbExtension = substr($newFileName, strrpos($newFileName, '.')+1);
		if (file_exists($path."/".$this->thumbFileName)) {
			$this->thumbSize = round((filesize($path."/".$this->thumbFileName)/1024), 0);
		}
		$this->upload->uploadedFiles[$this->field] = $this;
	}
	function setThumbSize($width, $height) {
		$this->thumbWidth = $width;
		$this->thumbHeight = $height;
		$this->upload->uploadedFiles[$this->field] = $this;
	}
	function setImageSize($width, $height) {
		$this->imageWidth = $width;
		$this->imageHeight = $height;
		$this->upload->uploadedFiles[$this->field] = $this;
	}
	
	function getFileName() {
		return $this->fileName;
	}
	function getThumbFileName() {
		return $this->thumbFileName;
	}
}
?>
