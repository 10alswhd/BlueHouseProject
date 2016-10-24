-- Base class for all versioned models
CREATE TABLE `VersionedModel` (
    `BlobId`            INTEGER(11)    NOT NULL,
    `VersionId`         BINARY(64)     NOT NULL,
    `IsTip`             BOOLEAN        NOT NULL,
    PRIMARY KEY (`BlobId`,`VersionId`),
    KEY `model_tip_index` (`BlobId`,`IsTip`)
) ENGINE=InnoDB;

-- Tracks changes to models
CREATE TABLE `History`
(
    `ModelBlobId`       INTEGER(11)    NOT NULL,
    `ModelVersionId`    BINARY(64)     NOT NULL,
    `ModelParentId`     BINARY(64),
    `ModelType`         VARCHAR(10)    NOT NULL,
    `Action`            INTEGER(11)    NOT NULL,
    `Timestamp`         TIMESTAMP      NOT NULL DEFAULT CURRENT_TIMESTAMP,
    `User`              VARCHAR(50)    NOT NULL,
    `Signature`         BINARY(100)    NOT NULL,
    
    PRIMARY KEY (`ModelBlobId`,`ModelVersionId`,`ModelParentId`),
    CONSTRAINT `history_parent_constraint` FOREIGN KEY (`ModelBlobId`, `ModelParentId`) REFERENCES `VersionedModel` (`BlobId`, `VersionId`),
    CONSTRAINT `history_version_constraint` FOREIGN KEY (`ModelBlobId`, `ModelVersionId`) REFERENCES `VersionedModel` (`BlobId`, `VersionId`)
) ENGINE=InnoDB;

-- An example of a versioned model
CREATE TABLE `Comment`
(
    `CommentId`         INTEGER(11)    NOT NULL,
    `CommentVersionId`  BINARY(64)     NOT NULL,
    `User`              VARCHAR(50)    NOT NULL,
    `Body`              TEXT           NOT NULL,
    
    PRIMARY KEY (`CommentId`,`CommentVersionId`),
    CONSTRAINT `comment_fk_constraint` FOREIGN KEY (`CommentId`, `CommentVersionId`) REFERENCES `VersionedModel` (`BlobId`, `VersionId`)
) ENGINE=InnoDB;
