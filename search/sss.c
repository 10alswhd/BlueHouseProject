NTSTATUS QueryDirectoryInfo(__in PFILE_OBJECT FileObject,
    						__in PIRP RelatedIrp, 
							__in PUNICODE_STRING SearchKeywords,
							__out PVOID Buffer,
							__in ULONG Length,
							__out PULONG ResultLength)
{
	PIRP Irp;
	NTSTATUS Status;
	KEVENT IrpEvent;
	PVOID KernelBuff;	
	KEVENT CompleteEvent;
	PDEVICE_OBJECT Device;
	IO_STATUS_BLOCK IoStatus;
	PIO_STACK_LOCATION IoStackLocation;
	UNICODE_STRING KernelSearchKeywords;
	PIO_STACK_LOCATION NextStackLocation;
	


	Device = IoGetDeviceAttachmentBaseRef(IoGetRelatedDeviceObject(FileObject));
	if (Device == NULL)
	{
		return STATUS_INVALID_DEVICE_REQUEST;
	}

	Irp = IoAllocateIrp(Device->StackSize,FALSE);
	if (Irp == NULL)
	{
		ObDereferenceObject(Device);
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	KeInitializeEvent(&IrpEvent,NotificationEvent,FALSE);
	KeInitializeEvent(&CompleteEvent,NotificationEvent,FALSE);	

	//
	//	初始化IRP
	Irp->UserBuffer = Buffer;
	Irp->UserEvent = &IrpEvent;
	Irp->UserIosb = &IoStatus;
	Irp->Tail.Overlay.Thread = RelatedIrp->Tail.Overlay.Thread;
	Irp->Tail.Overlay.OriginalFileObject = FileObject;
	Irp->Flags = 0;
	Irp->RequestorMode = KernelMode;

	IoStackLocation = IoGetCurrentIrpStackLocation(RelatedIrp);
	NextStackLocation = IoGetNextIrpStackLocation(Irp);
	NextStackLocation->MajorFunction = IRP_MJ_DIRECTORY_CONTROL;
	NextStackLocation->MinorFunction = IRP_MN_QUERY_DIRECTORY;
	NextStackLocation->Flags = IoStackLocation->Flags;
	NextStackLocation->FileObject = FileObject;
	NextStackLocation->Parameters.QueryDirectory.FileName = SearchKeywords;
	NextStackLocation->Parameters.QueryDirectory.FileInformationClass = IoStackLocation->Parameters.QueryDirectory.FileInformationClass;
	NextStackLocation->Parameters.QueryDirectory.FileIndex = IoStackLocation->Parameters.QueryDirectory.FileIndex;
	NextStackLocation->Parameters.QueryDirectory.Length = Length;

	IoSetCompletionRoutine(Irp,CompleteRoutine,&CompleteEvent,TRUE,TRUE,TRUE);
	Status = IoCallDriver(Device,Irp);
	if (Status == STATUS_PENDING)
	{
		KeWaitForSingleObject(&CompleteEvent,Executive,KernelMode,FALSE,NULL);
	}
	
	Status = Irp->IoStatus.Status;

	if (ResultLength != NULL)
	{
		*ResultLength = Irp->IoStatus.Information;
	}

	IoFreeIrp(Irp);
	ObDereferenceObject(Device);

	return Status;
}
