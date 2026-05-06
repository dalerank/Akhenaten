package com.github.dalerank.akhenaten;

import android.app.Activity;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.os.ParcelFileDescriptor;
import android.provider.DocumentsContract;
import android.content.UriPermission;

import android.util.Log;

import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class FileManager {
    private static final String PREFS_NAME = "akhenaten_prefs";
    private static final String PREF_BASE_URI = "base_uri";
    private static Uri baseUri = Uri.EMPTY;
    private static final HashMap<Uri, HashMap<String, FileInfo>> directoryStructureCache = new HashMap<>();

    private static final int FILE_TYPE_DIR = 1;
    private static final int FILE_TYPE_FILE = 2;

    private static String decodeUrl(String encodedUrl) {
        StringBuilder decodedUrlBuilder = new StringBuilder();
        char[] charArray = encodedUrl.toCharArray();

        for (int i = 0; i < charArray.length; i++) {
            char currentChar = charArray[i];

            if (currentChar == '%' && i + 2 < charArray.length) {
                // Check if there are two characters following '%' for a valid encoded sequence
                char hex1 = charArray[i + 1];
                char hex2 = charArray[i + 2];

                try {
                    // Convert the two hexadecimal characters to a decimal value and append the corresponding character
                    int decimalValue = Integer.parseInt("" + hex1 + hex2, 16);
                    decodedUrlBuilder.append((char) decimalValue);
                    i += 2; // Skip the two characters processed
                } catch (NumberFormatException e) {
                    // Ignore invalid encoded sequence
                    decodedUrlBuilder.append(currentChar);
                }
            } else {
                // Append the character as it is
                decodedUrlBuilder.append(currentChar);
            }
        }

        return decodedUrlBuilder.toString();
    }

    @SuppressWarnings("unused")
    public static String getPharaohPath(AkhenatenMainActivity activity) {
        if (baseUri == Uri.EMPTY) {
            restoreBaseUri(activity);
        }
        return baseUri == Uri.EMPTY ? "" : baseUri.toString();
    }

    @SuppressWarnings("unused")
    public static int setBaseUri(String path) {
        directoryStructureCache.clear();
        return setBaseUri(Uri.parse(path));
    }

    static void clearCache() {
        directoryStructureCache.clear();
    }

    static boolean hasBaseUri() {
        return baseUri != Uri.EMPTY;
    }

    static boolean hasAccessibleBaseUri(Context context) {
        if (baseUri == Uri.EMPTY) {
            restoreBaseUri(context);
        }
        return isUriAccessible(context, baseUri);
    }

    static Uri getBaseUri(Context context) {
        if (baseUri == Uri.EMPTY) {
            restoreBaseUri(context);
        }
        return baseUri;
    }

    static String getDisplayName(Context context) {
        Uri uri = getBaseUri(context);
        if (uri == null || Uri.EMPTY.equals(uri)) {
            return "";
        }

        try {
            String treeId = DocumentsContract.getTreeDocumentId(uri);
            int separator = treeId.lastIndexOf(':');
            if (separator >= 0 && separator + 1 < treeId.length()) {
                return treeId.substring(separator + 1);
            }
            return treeId;
        } catch (Exception e) {
            Log.w("akhenaten", "Unable to resolve display name for stored URI", e);
            return uri.toString();
        }
    }

    static void restoreBaseUri(Context context) {
        try {
            String uri = context.getSharedPreferences(PREFS_NAME, Context.MODE_PRIVATE).getString(PREF_BASE_URI, "");
            if (uri != null && !uri.isEmpty()) {
                Uri restoredUri = Uri.parse(uri);
                if (isUriAccessible(context, restoredUri)) {
                    setBaseUri(restoredUri);
                } else {
                    setBaseUri(Uri.EMPTY);
                    persistBaseUri(context, Uri.EMPTY);
                }
            }
        } catch (Exception e) {
            Log.e("akhenaten", "Error in restoreBaseUri: " + e);
            baseUri = Uri.EMPTY;
        }
    }

    private static void persistBaseUri(Context context, Uri uri) {
        try {
            context.getSharedPreferences(PREFS_NAME, Context.MODE_PRIVATE)
                    .edit()
                    .putString(PREF_BASE_URI, uri == Uri.EMPTY ? "" : uri.toString())
                    .apply();
        } catch (Exception e) {
            Log.e("akhenaten", "Error in persistBaseUri: " + e);
        }
    }

    static int setBaseUri(Uri newUri) {
        try {
            if (newUri == null || Uri.EMPTY.equals(newUri)) {
                baseUri = Uri.EMPTY;
                FileInfo.base = null;
                return 0;
            }
            baseUri = newUri;
            FileInfo.base = new FileInfo(DocumentsContract.getTreeDocumentId(newUri), null,
                    DocumentsContract.Document.MIME_TYPE_DIR, 0, Uri.EMPTY);
            return 1;
        } catch (Exception e) {
            Log.e("akhenaten", "Error in setBaseUri: " + e);
            return 0;
        }
    }

    static int setBaseUri(Context context, Uri newUri) {
        int result = setBaseUri(newUri);
        persistBaseUri(context, result != 0 ? newUri : Uri.EMPTY);
        return result;
    }

    private static boolean isUriAccessible(Context context, Uri uri) {
        if (context == null || uri == null || Uri.EMPTY.equals(uri)) {
            return false;
        }

        try {
            List<UriPermission> permissions = context.getContentResolver().getPersistedUriPermissions();
            boolean hasPermission = false;
            for (UriPermission permission : permissions) {
                if (uri.equals(permission.getUri()) && permission.isReadPermission()) {
                    hasPermission = true;
                    break;
                }
            }

            if (!hasPermission) {
                return false;
            }

            Uri documentUri = DocumentsContract.buildDocumentUriUsingTree(uri, DocumentsContract.getTreeDocumentId(uri));
            Cursor cursor = context.getContentResolver().query(
                    documentUri,
                    new String[] { DocumentsContract.Document.COLUMN_DOCUMENT_ID },
                    null,
                    null,
                    null);
            if (cursor == null) {
                return false;
            }
            cursor.close();
            return true;
        } catch (Exception e) {
            Log.w("akhenaten", "Stored base URI is no longer accessible", e);
            return false;
        }
    }

    private static HashMap<String, FileInfo> getDirectoryContents(Activity activity, FileInfo dir) {
        if (!dir.isDirectory()) {
            return new HashMap<>();
        }
        return getDirectoryContents(activity, dir.getUri());
    }

    private static HashMap<String, FileInfo> getDirectoryContents(Activity activity, Uri dir) {
        HashMap<String, FileInfo> result = directoryStructureCache.get(dir);
        if (result != null) {
            return result;
        }
        result = new HashMap<>();
        Uri children = DocumentsContract.buildChildDocumentsUriUsingTree(dir, DocumentsContract.getDocumentId(dir));
        String[] columns = new String[] {
                DocumentsContract.Document.COLUMN_DOCUMENT_ID,
                DocumentsContract.Document.COLUMN_DISPLAY_NAME,
                DocumentsContract.Document.COLUMN_MIME_TYPE,
                DocumentsContract.Document.COLUMN_LAST_MODIFIED
        };
        Cursor cursor = activity.getContentResolver().query(children, columns, null, null, null);
        if (cursor != null) {
            while (cursor.moveToNext()) {
                FileInfo fileInfo = new FileInfo(cursor.getString(0), cursor.getString(1), cursor.getString(2),
                        cursor.getLong(3), dir);
                result.put(cursor.getString(1).toLowerCase(), fileInfo);
            }
            cursor.close();
        }
        directoryStructureCache.put(dir, result);
        return result;
    }

    private static String normalizeRelativePath(String filePath) {
        if (filePath == null) {
            return "";
        }

        String normalized = filePath.replace('\\', '/');
        if (baseUri != Uri.EMPTY) {
            String base = baseUri.toString();
            if (normalized.startsWith(base)) {
                normalized = normalized.substring(base.length());
            }
        }

        while (normalized.startsWith("/")) {
            normalized = normalized.substring(1);
        }

        if (normalized.startsWith("./")) {
            normalized = normalized.substring(2);
        }

        while (normalized.endsWith("/")) {
            normalized = normalized.substring(0, normalized.length() - 1);
        }

        if (normalized.equals(".")) {
            return "";
        }

        return normalized;
    }

    private static FileInfo findFile(Activity activity, FileInfo folder, String fileName) {
        return getDirectoryContents(activity, folder).get(fileName.toLowerCase());
    }

    private static FileInfo getDirectoryFromPath(Activity activity, String[] path) {
        FileInfo currentDir = FileInfo.base;

        for (int i = 0; i < path.length - 1; ++i) {
            if (path[i] == null || path[i].isEmpty() || ".".equals(path[i])) {
                continue;
            }
            currentDir = findFile(activity, currentDir, path[i]);
            if (currentDir == null || !currentDir.isDirectory()) {
                return null;
            }
        }
        return currentDir;
    }

    private static FileInfo getFileFromPath(AkhenatenMainActivity activity, String filePath) {
        try {
            if (baseUri == Uri.EMPTY) {
                return null;
            }
            String normalizedPath = normalizeRelativePath(filePath);
            if (normalizedPath.isEmpty()) {
                return FileInfo.base;
            }

            String[] filePart = normalizedPath.split("[\\\\/]");
            FileInfo dirInfo = getDirectoryFromPath(activity, filePart);
            if (dirInfo == null) {
                return null;
            }
            return findFile(activity, dirInfo, filePart[filePart.length - 1]);
        } catch (Exception e) {
            Log.e("akhenaten", "Error in getFileFromPath: " + e);
            return null;
        }
    }

    @SuppressWarnings("unused")
    public static FileInfo[] getDirectoryFileList(AkhenatenMainActivity activity, String dir, int type, String ext) {
        ArrayList<FileInfo> fileList = new ArrayList<>();

        if (baseUri == Uri.EMPTY) {
            return new FileInfo[0];
        }
        FileInfo lookupDir = FileInfo.base;
        String normalizedDir = normalizeRelativePath(dir);
        if (!normalizedDir.isEmpty()) {
            normalizedDir += "/.";
            lookupDir = getDirectoryFromPath(activity, normalizedDir.split("[\\\\/]"));
            if (lookupDir == null) {
                return new FileInfo[0];
            }
        }
        for (FileInfo file : getDirectoryContents(activity, lookupDir).values()) {
            if (((type & FILE_TYPE_FILE) == 0 && !file.isDirectory()) ||
                    ((type & FILE_TYPE_DIR) == 0 && file.isDirectory())) {
                continue;
            }
            if (!file.isDirectory() && !ext.isEmpty()) {
                String fileName = file.getName();
                int extCharPos = fileName.lastIndexOf('.');
                String currentExtension = fileName.substring(extCharPos + 1);
                if (currentExtension.equalsIgnoreCase(ext)) {
                    fileList.add(file);
                }
            } else {
                fileList.add(file);
            }
        }
        FileInfo[] result = new FileInfo[fileList.size()];
        return fileList.toArray(result);
    }

    public static boolean deleteFile(AkhenatenMainActivity activity, String filePath) {
        try {
            FileInfo fileInfo = getFileFromPath(activity, filePath);
            if (fileInfo == null) {
                return false;
            }
            HashMap<String, FileInfo> dirList = directoryStructureCache.get(fileInfo.getParentUri());
            if (dirList != null) {
                dirList.remove(fileInfo.getName().toLowerCase());
            }
            return DocumentsContract.deleteDocument(activity.getContentResolver(), fileInfo.getUri());
        } catch (Exception e) {
            Log.e("akhenaten", "Error in deleteFile: " + e);
            return false;
        }
    }

    private static FileInfo ensureDirectoryPath(AkhenatenMainActivity activity, String dirPath) {
        if (baseUri == Uri.EMPTY) {
            return null;
        }

        String normalizedPath = normalizeRelativePath(dirPath);
        if (normalizedPath.isEmpty()) {
            return FileInfo.base;
        }

        String[] parts = normalizedPath.split("[\\\\/]");
        FileInfo currentDir = FileInfo.base;
        for (String rawPart : parts) {
            if (rawPart == null || rawPart.isEmpty() || ".".equals(rawPart)) {
                continue;
            }

            FileInfo nextDir = findFile(activity, currentDir, rawPart);
            if (nextDir == null) {
                Uri createdDirUri;
                try {
                    createdDirUri = DocumentsContract.createDocument(
                            activity.getContentResolver(),
                            currentDir.getUri(),
                            DocumentsContract.Document.MIME_TYPE_DIR,
                            rawPart);
                } catch (FileNotFoundException e) {
                    Log.e("akhenaten", "Error creating directory: " + rawPart, e);
                    return null;
                }
                if (createdDirUri == null) {
                    return null;
                }

                nextDir = new FileInfo(
                        DocumentsContract.getDocumentId(createdDirUri),
                        rawPart,
                        DocumentsContract.Document.MIME_TYPE_DIR,
                        System.currentTimeMillis(),
                        currentDir.getUri());

                HashMap<String, FileInfo> dirCache = directoryStructureCache.get(currentDir.getUri());
                if (dirCache != null) {
                    dirCache.put(rawPart.toLowerCase(), nextDir);
                }
            }

            if (!nextDir.isDirectory()) {
                return null;
            }
            currentDir = nextDir;
        }

        return currentDir;
    }

    @SuppressWarnings("unused")
    public static boolean createDirectories(AkhenatenMainActivity activity, String dirPath) {
        try {
            return ensureDirectoryPath(activity, dirPath) != null;
        } catch (Exception e) {
            Log.e("akhenaten", "Error in createDirectories: " + e);
            return false;
        }
    }

    private static boolean deleteDocumentRecursively(Activity activity, FileInfo fileInfo) {
        if (fileInfo == null) {
            return false;
        }

        try {
            if (fileInfo.isDirectory()) {
                HashMap<String, FileInfo> children = new HashMap<>(getDirectoryContents(activity, fileInfo));
                for (FileInfo child : children.values()) {
                    if (!deleteDocumentRecursively(activity, child)) {
                        return false;
                    }
                }
            }

            HashMap<String, FileInfo> dirList = directoryStructureCache.get(fileInfo.getParentUri());
            if (dirList != null && fileInfo.getName() != null) {
                dirList.remove(fileInfo.getName().toLowerCase());
            }
            directoryStructureCache.remove(fileInfo.getUri());
            return DocumentsContract.deleteDocument(activity.getContentResolver(), fileInfo.getUri());
        } catch (Exception e) {
            Log.e("akhenaten", "Error in deleteDocumentRecursively: " + e);
            return false;
        }
    }

    @SuppressWarnings("unused")
    public static boolean deleteDirectory(AkhenatenMainActivity activity, String dirPath) {
        try {
            String normalizedPath = normalizeRelativePath(dirPath);
            if (normalizedPath.isEmpty() || normalizedPath.equalsIgnoreCase("Save")) {
                Log.w("akhenaten", "Refusing to delete protected directory: " + normalizedPath);
                return false;
            }

            FileInfo dirInfo = getFileFromPath(activity, normalizedPath);
            if (dirInfo == null || !dirInfo.isDirectory()) {
                return false;
            }
            return deleteDocumentRecursively(activity, dirInfo);
        } catch (Exception e) {
            Log.e("akhenaten", "Error in deleteDirectory: " + e);
            return false;
        }
    }

    @SuppressWarnings("unused")
    public static int openFileDescriptor(AkhenatenMainActivity activity, String filePath, String mode) {
        try {
            if (baseUri == Uri.EMPTY) {
                return 0;
            }
            filePath = normalizeRelativePath(filePath);
            String internalMode = "";
            boolean isWrite = false;
            // Either "r" or "w"
            if (mode.indexOf('r') != -1) {
                internalMode += "r";
            }
            if (mode.indexOf('w') != -1) {
                internalMode += "w";
                isWrite = true;
            }

            String[] fileParts = filePath.split("[\\\\/]");
            String fileName = fileParts[fileParts.length - 1];
            FileInfo folderInfo = getDirectoryFromPath(activity, fileParts);
            if (folderInfo == null) {
                return 0;
            }
            FileInfo fileInfo = findFile(activity, folderInfo, fileName);
            Uri fileUri;
            if (fileInfo == null) {
                if (!isWrite) {
                    return 0;
                }
                fileUri = DocumentsContract.createDocument(activity.getContentResolver(),
                        folderInfo.getUri(), "application/octet-stream", fileName);
                if (fileUri == null) {
                    return 0;
                }
                HashMap<String, FileInfo> dirCache = directoryStructureCache.get(folderInfo.getUri());
                if (dirCache != null) {
                    fileInfo = new FileInfo(DocumentsContract.getDocumentId(fileUri),
                            fileName, "application/octet-stream", System.currentTimeMillis(), folderInfo.getUri());
                    dirCache.put(fileName.toLowerCase(), fileInfo);
                }
            } else {
                fileUri = fileInfo.getUri();
                if (isWrite) {
                    fileInfo.updateModifiedTime();
                }
            }
            ParcelFileDescriptor pfd = activity.getContentResolver().openFileDescriptor(fileUri, internalMode);
            return (pfd == null) ? 0 : pfd.detachFd();
        } catch (Exception e) {
            Log.e("akhenaten", "Error in openFileDescriptor: " + e);
            return 0;
        }
    }

    @SuppressWarnings("unused")
    public static class FileInfo {
        static FileInfo base;
        private final String documentId;
        private final String name;
        private final String mimeType;
        private final Uri parent;
        private long modifiedTime;
        private Uri uri;

        private FileInfo(String documentId, String name, String mimeType, long modifiedTime, Uri parent) {
            this.documentId = documentId;
            this.name = name;
            this.mimeType = mimeType;
            this.parent = parent;
            this.modifiedTime = modifiedTime / 1000;
            this.uri = Uri.EMPTY;
        }

        public String getName() {
            return this.name;
        }

        public long getModifiedTime() {
            return this.modifiedTime;
        }

        public void updateModifiedTime() {
            this.modifiedTime = System.currentTimeMillis() / 1000;
        }

        public boolean isDirectory() {
            return this.mimeType.equals(DocumentsContract.Document.MIME_TYPE_DIR);
        }

        Uri getUri() {
            if (baseUri != Uri.EMPTY && this.uri == Uri.EMPTY) {
                this.uri = DocumentsContract.buildDocumentUriUsingTree(baseUri, this.documentId);
            }
            return this.uri;
        }

        Uri getParentUri() {
            return this.parent;
        }
    }
}
