/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

        Authors:    David Ducos, Percona (david dot ducos at percona dot com)
*/

#ifndef _src_myloader_h
#define _src_myloader_h

enum job_type { JOB_RESTORE, JOB_WAIT, JOB_SHUTDOWN};

struct thread_data {
  struct configuration *conf;
  MYSQL *thrconn;
  gchar *current_database;
  guint thread_id;
};

struct configuration {
  GAsyncQueue *database_queue;
  GAsyncQueue *table_queue;
  GAsyncQueue *data_queue;
  GAsyncQueue *post_table_queue;
  GAsyncQueue *post_queue;
  GAsyncQueue *ready;
  GAsyncQueue *pause_resume;
  GList *table_list;
  GHashTable *table_hash;
//  GList *schema_create_list;
  GList *checksum_list;
  GList *metadata_list;
  GMutex *mutex;
  int done;
};

struct job {
  enum job_type type;
  struct restore_job *job_data;
  GAsyncQueue * queue;
  char * use_database;
};

struct db_table {
  char *database;
  char *real_database;
  char *table;
  char *real_table;
  char *filename;
  guint64 rows;
  GAsyncQueue * queue;
  GList * restore_job_list;
  guint current_threads;
  guint max_threads;
  GMutex *mutex;
  GString *indexes;
  GString *constraints;
  guint count;
  gboolean schema_created;
  GDateTime * start_time;
  GDateTime * start_index_time;
  GDateTime * finish_time;
};

enum file_type { INIT, SCHEMA_CREATE, SCHEMA_TABLE, DATA, SCHEMA_VIEW, SCHEMA_TRIGGER, SCHEMA_POST, CHECKSUM, METADATA_TABLE, METADATA_GLOBAL, RESUME, IGNORED, LOAD_DATA, SHUTDOWN};
enum restore_job_type { JOB_RESTORE_SCHEMA_FILENAME, JOB_RESTORE_FILENAME, JOB_RESTORE_SCHEMA_STRING, JOB_RESTORE_STRING };

struct restore_job {
  enum restore_job_type type;
  struct db_table * dbt;
  char *database;
  char *filename;
  GString *statement;
  guint part;
  guint sub_part;
  const char *object;
};

#endif
